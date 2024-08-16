#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGUMENTS 10

/**  Fonction pour lire la ligne de commande et diviser en arguments */
char **split_string(int max_argument)
{
	char *buffer = NULL;
	size_t len = 0;
	ssize_t nread;
	char *token;
	int i = 0;

	printf("§ ");
	nread = getline(&buffer, &len, stdin);
	if (nread == -1)
	{
		free(buffer);
		return (NULL);
	}
	printf("1-debogage: %s\n", buffer);

	/** Supprimer le retour à la ligne (\n) en fin de commande */
	buffer[strcspn(buffer, "\n")] = '\0';

	/** Vérifier si la commande est "exit" */
	if (strcmp(buffer, "exit") == 0)
	{
		free(buffer);
		exit(0); /** Quitter le programme*/
	}

	char **argv = malloc(max_argument * sizeof(char *));
	if (argv == NULL)
	{
		perror("malloc");
		free(buffer);
		exit(EXIT_FAILURE);
	}

	printf("2-debogage\n"); /** Debogae */

	token = strtok(buffer, " \n");
	while (token != NULL && i < max_argument - 1)
	{
		argv[i] = strdup(token); /** *chaînes sont dupliquées */
		if (argv[i] == NULL)
		{
			perror("strdup");
			free(buffer);
			for (int j = 0; j < i; j++) /** *Nettoyer la mémoire déjà allouée */
				free(argv[j]);
			free(argv);
			exit(EXIT_FAILURE);
		}
		printf("argv[%d] = %s\n", i, argv[i]); /** Débogage */
		i++;
		token = strtok(NULL, " \n");
	}
	argv[i] = NULL;

	free(buffer);

	printf("3-debogage\n"); /** Debogae */

	return (argv);
}

/** Fonction pour trouver le chemin complet d'une commande */
char *find_command_path(char *command)
{
	/** verifier si la commande est entré avec un chemin "command[0]""*/
	if (command[0] == '/' && access(command, X_OK) == 0)
	{
		return strdup(command);
	}
	
	char *path_env = getenv("PATH");
	if (path_env == NULL)
	{
		return (NULL); // PATH n'existe pas
	}

	printf("PATH: %s\n", path_env); /** Debogae */

	char *path = strdup(path_env);		 /** Copier PATH pour le manipuler */
	char *directory = strtok(path, ":"); /** séparer les chemins de variables */
	char *full_path = malloc(1024);		 /** Buffer pour stocker le chemin complet */

	if (full_path == NULL)
	{
		perror("malloc");
		free(path);
		return NULL;
	}

	while (directory != NULL)
	{
		// Copier le répertoire actuel dans full_path
		strcpy(full_path, directory);

		// Ajouter un slash et la commande au chemin
		strcat(full_path, "/");
		strcat(full_path, command);

		printf("Testing path: %s\n", full_path); /** débogage */

		// Vérifier si le fichier existe et est exécutable
		if (access(full_path, X_OK) == 0)
		{
			free(path);
			return (full_path); /**Chemin trouvé*/
		}

		/** Passer au répertoire suivant dans PATH */
		directory = strtok(NULL, ":");
	}

	free(full_path);
	free(path);
	return (NULL); /**Commande non trouvée dans les répertoires de PATH */
}

/** Fonction pour exécuter la commande*/
int s_s_shell(int max_argument)
{
	pid_t pid;
	int status;

	char **argv = split_string(max_argument);

	if (argv == NULL || argv[0] == NULL)
	{
		free(argv);
		return (-1); /* pas de commande*/
	}

	for (int i = 0; argv[i] != NULL; i++)
	{
		printf("argv[%d] = %s\n", i, argv[i]); /** débogage */
	}
	char *command_path = find_command_path(argv[0]);
	if (command_path == NULL)
	{
		printf("Commande introuvable : %s\n", argv[0]);
		free(argv);
		return -1;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Erreur lors du fork");
		free(argv);
		free(command_path);
		exit(EXIT_FAILURE);
	}
	printf("hello\n");
	if (pid == 0)
	{
		/** Processus enfant */
		execv(command_path, argv);
		perror("Erreur lors de execve");
		free(argv);
		free(command_path);
		exit(EXIT_FAILURE);
	}
	else
	{
		/** Processus parent */
		waitpid(pid, &status, 0);
		printf("Statut du processus fils : %d\n", WEXITSTATUS(status));
	}

	free(argv);
	free(command_path);
	return 0;
}

int main()

{
	while (1)
	{
		s_s_shell(MAX_ARGUMENTS);
	}

	return 0;
}
