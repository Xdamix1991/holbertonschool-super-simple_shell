#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
int main(int ac, char **av)
{
	int i;
	while (*av != NULL)
	{
		printf("%s\n", *av);
		av++;
	}
	return (0);
}
