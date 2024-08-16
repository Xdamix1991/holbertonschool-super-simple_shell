#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int *split_string(void)

{
	char *buffer;
	size_t len;
	buffer = NULL;
	char *token;

	size_t nread;
	len = 0;

	while (1)
	{
		printf("§ ");
		nread = getline(&buffer, &len, stdin);

		if (nread == -1)
		{
			break;
		}

		token = strtok(buffer, " ");
		while (token != NULL)
		{
			printf("Token: %s\n", token);
			token = strtok(NULL, " ");
		}
	}

	free(buffer);
	return (token);
}
