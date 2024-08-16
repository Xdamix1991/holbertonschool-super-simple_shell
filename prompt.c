#define _GNU_SOURCE
#define  _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(void)

{
	char *buffer;
	size_t len;

	buffer = NULL;
	size_t nread;
	len = 0;


	nread = getline(&buffer, &len, stdin);
	rintf("%s\n", buffer);

	free(buffer);
	return(0);
}
