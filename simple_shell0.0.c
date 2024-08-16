#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGUMENTS 10

// Fonction pour lire la ligne de commande et diviser en arguments
char **split_string(int max_argument)
{
    char *buffer = NULL;
    size_t len = 0;
    ssize_t nread;

    printf("§ ");
    nread = getline(&buffer, &len, stdin);
    if (nread == -1)
    {
        free(buffer);
        return NULL; // Fin de l'entrée ou erreur
    }

    char **argv = malloc(max_argument * sizeof(char *));
    char *token;
    int i = 0;

    token = strtok(buffer, " \n");
    while (token != NULL && i < max_argument - 1)
    {
        argv[i++] = token;
        token = strtok(NULL, " \n");
    }
    argv[i] = NULL; // Terminer par NULL pour execve

    // Note : Pas besoin de libérer `buffer` ici car les pointeurs `argv[i]`
    // pointent vers les parties de `buffer`.
    return argv;
}

// Fonction pour trouver le chemin complet d'une commande
char *find_command_path(char *command)
{
    char *path_env = getenv("PATH");
    if (path_env == NULL)
    {
        return NULL; // PATH n'existe pas
    }

    char *path = strdup(path_env); // Copier PATH pour le manipuler
    char *directory = strtok(path, ":");
    char *full_path = malloc(1024); // Buffer pour stocker le chemin complet

    while (directory != NULL)
    {
        snprintf(full_path, 1024, "%s/%s", directory, command);
        if (access(full_path, X_OK) == 0)
        { // Vérifier si le fichier est exécutable
            free(path);
            return full_path; // Chemin trouvé
        }
        directory = strtok(NULL, ":");
    }

    free(full_path);
    free(path);
    return NULL; // Commande non trouvée dans les répertoires de PATH
}

// Fonction pour exécuter la commande
int s_s_shell(int max_argument)
{
    pid_t pid;
    int status;

    char **argv = split_string(max_argument);
    if (argv == NULL || argv[0] == NULL)
    {
        free(argv);
        return -1; // Aucun argument trouvé ou erreur de lecture
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

    if (pid == 0)
    {
        // Processus enfant
        execv(command_path, argv);
        perror("Erreur lors de execve");
        free(argv);
        free(command_path);
        exit(EXIT_FAILURE);
    }
    else
    {
        // Processus parent
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
