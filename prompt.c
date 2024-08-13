#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Fonction pour afficher tous les arguments sans utiliser 'ac' */
void print_arguments(char **av)
{
	for (int i = 0; av[i] != NULL; i++)
	{
		printf("Argument %d: %s\n", i, av[i]);
	}
}

/* Fonction pour lire une ligne de l'entrée standard et l'afficher */
void read_and_print_line(void)
{
	char *line = NULL;

	size_t len = 0;
	ssize_t nread;

	/* Affiche le prompt */
	printf("$ ");

	/* Lire la ligne entrée par l'utilisateur */
	nread = getline(&line, &len, stdin);

	/* Vérifier si la ligne a été lue correctement */
	while (nread != -1)
	{
		/* Affiche la ligne saisie par l'utilisateur */
		printf("%s", line);

		/* Affiche à nouveau le prompt */
		printf("$ ");

		/* Lire la prochaine ligne */
		nread = getline(&line, &len, stdin);
	}

	/* Libérer la mémoire allouée pour la ligne */
	free(line);
}

/* Fonction pour diviser une chaîne de caractères en mots (tokens) */
char **split_string(char *str)
{

	int buffer_size = 64, i = 0;
	char **tokens = malloc(buffer_size * sizeof(char *));
	char *start = str, *end;

	if (!tokens)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	while (*start != '\0')
	{
		/* Ignorer les espaces initiaux */

		while (isspace(*start)) start++;

		/* Trouver la fin du mot */
		end = start;

		while (*end != '\0' && !isspace(*end)) end++;

		/* Copier le mot dans le tableau de tokens */
		if (start != end)
		{
			int length = end - start;

			tokens[i] = malloc(length + 1);
			strncpy(tokens[i], start, length);
			tokens[i][length] = '\0';
			i++;

			if (i >= buffer_size)
			{
				buffer_size += 64;
				tokens = realloc(tokens, buffer_size * sizeof(char *));
				if (!tokens)
				{
					fprintf(stderr, "Reallocation error\n");
					exit(EXIT_FAILURE);
				}
			}
		}

		start = end;
	}
	tokens[i] = NULL;
	return (tokens);
}

/* Fonction principale */
int main(int ac, char **av)
{

	/* Eviter un avertissement pour la variable inutilisée */
	(void)ac;

	/* Exercice 0: Imprimer tous les arguments */
	print_arguments(av);

	/* Exercice 1: Lire une ligne et l'afficher */
	read_and_print_line();

	return (0);
}
