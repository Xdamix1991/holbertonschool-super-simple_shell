#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGUMENTS 10

/**  Fonction pour lire la ligne de commande et diviser en arguments */
char **split_string(int max_argument, char *command)
{
	char *buffer;

	/*Si une commande est fournie (mode non_interactif) */
	if (command != NULL)
	{
		buffer = strdup(command); /* Créé une copie de la commande */
		if (buffer == NULL)
		{
			perror("Erreur lors de la duplication de la commande");
			return (NULL);
		}
	}
		else
	{

		/* Mode interactif : Lire la commande depuis l'entrée standard */
		buffer = NULL;
		size_t len = 0;
		ssize_t nread;

		printf("§ ");
		nread = getline(&buffer, &len, stdin);
		if (nread == -1)
		{
			perror("Erreur lors de la lecture de la ligne de commande");
			free(buffer);
			return (NULL);
		}

	/** Supprimer le retour à la ligne (\n) en fin de commande */
		buffer[strcspn(buffer, "\n")] = '\0';

	/** Vérifier si la commande est "exit" */
		if (strcmp(buffer, "exit") == 0)
		{
			free(buffer);
			exit(0); /** Quitter le programme*/
		}
	}

	char **argv = malloc(max_argument * sizeof(char *));
	if(argv == NULL)
	{
		perror("Erreur lors de l'allocation mémoire pour argv");
		free(buffer);
		return (NULL);
	}

	char *token;
	int i = 0;

	token = strtok(buffer, " \n");
	while (token != NULL && i < max_argument - 1)
	{
		argv[i] = strdup(token); /* Duplique chaque token */
		if (argv[i] == NULL)
		{
			perror("Erreur lors de la duplication du token");
			for (int j = 0; j < i; j++)
			{
				free(argv[j]);
			}
			free(argv);
			free(buffer);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " \n");
	}
	argv[i] = NULL;

	free(buffer); /* On peut maintant libérer buffer */

	return (argv);
}

/** Fonction pour trouver le chemin complet d'une commande */
char *find_command_path(char *command)
{
	char *path_env = getenv("PATH");
	if (path_env == NULL)
	{
		perror("Erreur : path non défini");
		return (NULL); // PATH n'existe pas
	}

	char *path = strdup(path_env);		 /** Copier PATH pour le manipuler */
	if (path == NULL)
	{
		perror("Erreur lors de la duplication de PATH");
		return (NULL);
	}
	char *full_path = malloc(1024);		 /** Buffer pour stocker le chemin complet */
	if (full_path == NULL)
	{
		free (path);
		perror("Erreur lors de l'allocation mémoire full_path");
		return (NULL);
	}
	char *directory = strtok(path, ":"); /** séparer les chemins de variables */
	while (directory != NULL)
	{
		// Copier le répertoire actuel dans full_path
		strcpy(full_path, directory);
		// Ajouter un slash et la commande au chemin
		strcat(full_path, "/");
		strcat(full_path, command);

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

void free_argv(char **argv)
{
	if (argv != NULL)
	{
		for (int i = 0; argv[i] != NULL; i++)
		{
			free(argv[i]); /*Libère chaque chaine */
		}
		free(argv); /* Libère le tableau de pointeurs */
	}
}

/** Fonction pour exécuter la commande*/
int s_s_shell(int max_argument)
{
	pid_t pid;
	int status;

	char **argv = split_string(max_argument, NULL);
	if (argv == NULL || argv[0] == NULL)
	{
		free_argv(argv);
		return (-1); /* pas de commande*/
	}

	char *command_path = find_command_path(argv[0]);
	if (command_path == NULL)
	{
		printf("Commande introuvable : %s\n", argv[0]);
		free_argv(argv);
		return -1;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Erreur lors du fork");
		free_argv(argv);
		free(command_path);
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		/** Processus enfant */
		execv(command_path, argv);
		perror("Erreur lors de execve");
		free_argv(argv);
		free(command_path);
		exit(EXIT_FAILURE);
	}
	else
	{
		/** Processus parent */
		waitpid(pid, &status, 0);
		printf("Statut du processus fils : %d\n", WEXITSTATUS(status));
	}

	free_argv(argv);
	free(command_path);
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		/* Mode non-interactif */
		char command[1024] = ""; /*S'assurer d'avoir assez de place pour la commande complète */
		strcat(command, argv[1]);

		for (int i = 2; i < argc; i++)
		{
			strcat(command, " ");
			strcat(command, argv[i]);
		}
		char **argv_non_interactif = split_string(MAX_ARGUMENTS, command);
		if (argv_non_interactif == NULL)
		{
			perror("Erreur lors de la création des arguments non-interactifs");
			return (-1);
		}
		char *command_path = find_command_path(argv_non_interactif[0]);
		if (command_path == NULL)
		{
			printf("Commande introuvable : %s\n", argv_non_interactif[0]);
			free_argv(argv_non_interactif);
			return (-1);
		}

		execv(command_path, argv_non_interactif);
		perror("erreur lors execve");
		free_argv(argv_non_interactif);
		free(command_path);
		exit(EXIT_FAILURE);
	}
	else
	{
		/*Mode interactif */
		while (1)
		{
			s_s_shell(MAX_ARGUMENTS);
		}
	}
	return 0;
}
