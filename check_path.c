#include "main.h"


/**
 * find_command_path - Find the full path of a command using PATH environment variable.
 * @command: The command to find.
 *
 * Return: The full path of the command or NULL if not found.
 */
char *find_command_path(const char *command)
{
	char *path_env;
	char *path_copy;
	char *directory;
	char *full_path;

	if (command == NULL)
	{
		return (NULL);
	}

	/**  Check if the command is already an absolute path*/
	if (command[0] == '/' && access(command, X_OK) == 0)
	{
		return strdup(command);
	}

	/**Get PATH environment variable*/
	path_env = my_getenv("PATH");
	if (path_env == NULL)
	{
		return NULL; /** PATH not found*/
	}

	/** Duplicate the PATH variable to manipulate it*/
	path_copy = strdup(path_env);
	if (path_copy == NULL)
	{
		perror("strdup");
		return NULL;
	}

	/**Allocate memory for the full path*/
	full_path = malloc(1024);
	if (full_path == NULL)
	{
		perror("malloc");
		free(path_copy);
		return NULL;
	}

	/** Tokenize PATH variable and search for the command*/
	directory = strtok(path_copy, ":");
	while (directory != NULL)
	{
		/** Build the full path*/
		snprintf(full_path, 1024, "%s/%s", directory, command);

		/**Check if the file exists and is executable*/
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return full_path;
		}

		/**  Get the next directory in PATH*/
		directory = strtok(NULL, ":");
	}

	/**Clean up and return NULL if not found*/
	free(full_path);
	free(path_copy);
	return NULL;
}
