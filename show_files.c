#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "main.h"

int show_file(void)

{
	char *current_path;
	char **files;
	int file_count, i;

	current_path = get_current_path();
	if (current_path == NULL)
	{
		fprintf(stderr, "Error getting current path.\n");
		exit(EXIT_FAILURE);
	}

	files = show_dir(current_path, &file_count);
	if (files == NULL)
	{
		fprintf(stderr, "Error getting files in directory.\n");
		free(current_path);
		exit(EXIT_FAILURE);
	}
	printf("hello\n");
	printf("Files in directory '%s':\n", files);
	for (i = 0; i < file_count; i++)
	{

		printf("%s\n", files[i]);
		free(files[i]);
	}

	free(files);
	free(current_path);

	return (0);
}

int hello(void)
{
	show_file();
	return (0);
}
