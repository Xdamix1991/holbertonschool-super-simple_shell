#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

/**
 * my_getenv - Custom getenv to find the PATH environment variable.
 * @name: The name of the environment variable to find.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *my_getenv(const char *name)
{
	char **env;
	size_t name_len;
	const char *env_var;
	size_t i;

	if (name == NULL)
	{
		return (NULL);
	}

	name_len = 0;
	while (name[name_len] != '\0')
	{
		name_len++;
	}

	for (env = environ; *env != NULL; env++)
	{
		env_var = *env;

		for (i = 0; i < name_len; i++)
		{
			if (env_var[i] != name[i])
			{
				break;
			}
		}

		if (i == name_len && env_var[i] == '=')
		{
			return ((char *)(env_var + name_len + 1));
		}
	}

	return (NULL);
}
