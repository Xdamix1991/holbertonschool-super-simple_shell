#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "main.h"
#define BUFFER_SIZE 1024

char *get_current_path(void)
{

	char *path = malloc(BUFFER_SIZE);

	if (path == NULL)
	{
		perror("memory allocation");
		exit(EXIT_FAILURE);
	}

	if (getcwd(path, BUFFER_SIZE) == NULL)
	{
		perror("getcwd");
		fprintf(stderr, "directory not found\n");
		free(path);
		exit(EXIT_FAILURE);
	}

	return (path);
}

int main(void)
{
	char *p;

	p = get_current_path();
	printf("current PATH : %s\n", p);
	free(p);
	return (0);
}
