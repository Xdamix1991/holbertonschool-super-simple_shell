#define _GNU_SOURCE
#define  _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)

{
	char *buffer;
	size_t len;

	buffer = NULL;
	len = 0;


	getline(&buffer, &len, stdin);
	printf("%s\n", buffer);

	free(buffer);
	return(0);
}
