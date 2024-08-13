#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)

{
	char *buffer;
	size_t len;
	buffer = NULL;
	char *token;

	size_t nread;
	len = 0;

	nread = getline(&buffer, &len, stdin);
	printf("%s\n", buffer);

	if (nread == -1)
	{
		exit;
	}

	token = strtok(buffer, " ");
	while (token != NULL)
	{
		printf("Token: %s\n", token);
		token = strtok(NULL, " ");
	}
	free(buffer);
	return (0);
}
