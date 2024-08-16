#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "main.h"

char **show_dir(const char *name, int *file_count)

{
	DIR *d;
	struct dirent *dirp;
	char **file_list = NULL;
	int count = 0;

	d = opendir(name);
	if (d == NULL)
	{
		perror("opendir");
		fprintf(stderr, "Directory not found\n");
		exit(EXIT_FAILURE);
	}
	while ((dirp = readdir(d)) != NULL)
	{
		file_list = realloc(file_list, sizeof(char *) * (count + 1));
		if (file_list == NULL)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}
		count++;
	}
	closedir(d);
	*file_count = count;
	return (file_list);
}

