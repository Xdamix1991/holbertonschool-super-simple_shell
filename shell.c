#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	/* Commande et arguments pour execve */
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
	char *envp[] = {NULL}; /* Variables d'environnement (facultatif) */
	pid_t pid;
	int status;

	/* Boucle pour créer 5 processus enfants */
	for (int i = 0; i < 5; i++)
	{
		pid = fork(); /* Créer un nouveau processus enfant */

		if (pid == -1)
		{
			/* En cas d'erreur avec fork */
			perror("Erreur fork");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			/* Code du processus enfant */
			if (execve(argv[0], argv, envp) == -1)
			{
				/* Si execve échoue */
				perror("Erreur execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/* Code du processus parent */
			wait(&status); /* Attendre la fin du processus enfant */
			printf("Processus enfant %d terminé\n", i + 1);
		}
	}

	return (0);
}
