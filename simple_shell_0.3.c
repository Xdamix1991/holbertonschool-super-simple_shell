#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * free_argv - free momory allouée to all arguments.
 * @argv: array of pointer arguments.
 */
void free_argv(char **argv)
{
	int i;

	if (argv == NULL)
	{
		return;
	}

	for (i = 0; argv[i] != NULL; i++)
	{
		free(argv[i]);
	}

	free(argv);
}

/**
 *split_string - function .
 *@max_argument: The number of arguments.
 * This function reads and catchs the arguments (commands) passed on the prompt
 * Return: a pointer of arguments
 **/

/**  Fonction pour lire la ligne de commande et diviser en arguments */
char **split_string(int max_argument)
{
	int i = 0;
	char *token, **argv;
	char *buffer = NULL;
	size_t len = 0;
	ssize_t nread;

	/** using getline to get the commands */
	nread = getline(&buffer, &len, stdin);
	if (nread == -1)
	{
		free(buffer);
		exit(EXIT_SUCCESS);
	}
	else
		buffer[nread - 1] = '\0';
	/** allocating memory for arguments */
	argv = malloc(max_argument * sizeof(char *));
	if (argv == NULL)
	{
		perror("malloc");
		free(buffer);
		exit(EXIT_FAILURE);
	}
	/** strtok with " " and "if there is "\n" to extract each argument command*/
	token = strtok(buffer, " \n");
	while (token != NULL && i < max_argument - 1)
	{ /** put each token into agv[i] */
		argv[i] = strdup(token);
		if (argv[i] == NULL)
		{
			perror("strdup");
			free(buffer);
			free_argv(argv);
			exit(EXIT_FAILURE);
		}
		i++;
		token = strtok(NULL, " \n");
	}
	argv[i] = NULL;
	free(buffer);
	return (argv);
}

/**
 *execute_command - function .
 *@max_argument: The number of arguments.
 * This function excute the arguments (commands) passed to it
 * Return: 0 on sucsess
 **/

int execute_command(int max_argument, char **envp)

{
	pid_t pid;
	int statut;
	char **argv;
	char *command_path;

	argv = split_string(max_argument);/** call our function */
	if (argv == NULL || argv[0] == NULL)
	{
		free_argv(argv);
		return (-1);
	}
	command_path = find_command_path(argv[0]);/** check path command */
	if (command_path == NULL)
	{
		perror("PATH");
		free_argv(argv);
		return (-1);
	}
	pid = fork(); /** start processing arguments */
	if (pid == -1)
	{
		perror("fork");
		free_argv(argv);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(command_path, argv, envp) == -1)
		{
			perror(command_path);
			free(command_path);
			free_argv(argv);
			exit(EXIT_FAILURE);
		}
	}
		else
		{
			waitpid(pid, &statut, 0);
		}
		free(command_path);
	free_argv(argv);
	return (0);
}


/**
 *main - function to execute the programe shell
 *Return: 0 on sucsess
 */

int main(void)

{
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
		 printf(":) ");
		fflush(stdout);
		}

		if (execute_command(MAX_ARGUMENTS, NULL) == -1)
		{
			continue;
		}
		if (!isatty(STDIN_FILENO))
		{
			break;
		}
	}

	return (0);
}
