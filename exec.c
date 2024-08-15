#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	/* Commande à exécuter et ses arguments */
	char *argv[] = {"/bin/ls", "-l", NULL};

	/* Variables d'environnement (optionnelles, ici NULL) */
	char *envp[] = {NULL};

	/* Remplace le processus courant par le programme spécifié par argv[0] */
	if (execve(argv[0], argv, envp) == -1)
	{
		/* Si execve échoue, afficher un message d'erreur et quitter */
		perror("execve");
		exit(EXIT_FAILURE);
	}

	/* Ce code ne sera jamais atteint si execve réussit */
	printf("Cette ligne ne s'affichera pas si execve fonctionne correctement.\n");

	return (0);
}
