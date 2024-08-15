#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

char *get_current_path(void)
{
	ssize_t buffer_size = 1024; /* Taille initiale du buffer */
	char *path = malloc(buffer_size);

	if (path == NULL)
	{
		perror("memory allocation");
		exit(EXIT_FAILURE);
	}

	/* Boucle pour réessayer jusqu'à ce que getcwd réussisse */
	while (getcwd(path, buffer_size) == NULL)
	{
		if (errno == ERANGE)
		{
		/* Double la taille du buffer et réessaye */
			buffer_size *= 2;
			char *temp = realloc(path, buffer_size);

			if (temp == NULL)
			{
				perror("realloc");
				free(path);
				exit(EXIT_FAILURE);
			}

			path = temp;
		}
		else /* Poour toute autre erreur, si errno != ERANGE */
		{
			perror("getcwd");
			free(path);
			exit(EXIT_FAILURE);
		}
	}

	return (path);
}

int main(void)
{
	char *p;

	p = get_current_path();
	printf("current PATH: %s\n", p);
	free(p);

	return (0);
}

/*Petite amélioration de ton code pour avoir une memoire alloué dynamiquement ,
*ce qui évite les problème de mémoire s'il en manque, si l'erreur ne vient
*pas de la mémoire c'est bien de le savoir "errno != ERANGE" c'est 2 variable permet de le savoir .
*/

/*Lorsque tu utilises la fonction getcwd, celle-ci peut échouer pour plusieurs
raisons. Ces raisons sont signalées par la variable globale errno, qui est
 définie lorsque certaines fonctions échouent pour indiquer le type d'erreur qui s'est produite.

Le rôle de errno
errno est une variable globale qui est définie par les fonctions système
pour indiquer quel type d'erreur s'est produit lorsque la fonction échoue.
 Dans le contexte de getcwd, deux erreurs communes peuvent se produire :

ERANGE : Cette erreur signifie que le buffer que tu as passé à getcwd est
trop petit pour contenir le chemin complet. C'est pourquoi tu as besoin
de réallouer de la mémoire pour un buffer plus grand.

Autres erreurs (errno != ERANGE) : Si l'erreur n'est pas ERANGE,
cela signifie que l'échec de getcwd n'est pas dû à un problème de taille de buffer,
mais à une autre cause (comme des permissions insuffisantes, un chemin introuvable, etc.).*/


/**
*Initialisation :
*
*On commence avec une taille initiale de 1024 pour le buffer.
*La mémoire est allouée avec malloc.
*Boucle de réallocation :
*
*La fonction getcwd est appelée pour récupérer le chemin courant.
*Si getcwd échoue et que errno est ERANGE
*(ce qui signifie que le buffer est trop petit),
* la taille du buffer est doublée avec buffer_size *= 2, et realloc est utilisée pour agrandir la mémoire.
*Si realloc échoue (renvoie NULL), le programme affiche une erreur et libère la mémoire.

*Finalisation :
*
*Une fois que getcwd réussit, le chemin est retourné.
*Dans main, le chemin est affiché et la mémoire est libérée après usage.

*Pourquoi cette amélioration ?
*Souplesse : Le programme peut s'adapter à des chemins de répertoires
*de différentes tailles sans connaître à l'avance la taille exacte requise.
*Optimisation de la mémoire : La mémoire est allouée en fonction
*des besoins réels, minimisant les risques de gaspillage ou
*de manque de mémoire.
*Robustesse : Le programme gère les erreurs de manière appropriée,
* assurant qu'il ne plante pas et ne fuit pas de mémoire.
*/
