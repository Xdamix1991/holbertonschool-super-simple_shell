#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "main.h"

int arguments(int ac, char **av)
{
	int i;
	while (*av != NULL)
	{
		printf("%s\n", *av);
		av++;
	}
	return (0);
}
