#include <unistd.h>
#include <stdio.h>

int main()
{
	printf("Parent Process ID: %d\n", getppid());
	return (0);

}
