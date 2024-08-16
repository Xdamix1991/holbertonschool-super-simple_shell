#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int s_s_shell(char *command, int max_argument)

{

	command = split_string();

	for (i = 0; i < max_argument; i++)
	{
		pid = fork();
		printf("pid: %d\n", pid);

		if (pid == -1)
		{
			perror("faillure");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			execve(argv[0], argv, envp);

			perror("execve");
			exit(EXIT_FAILURE);
		}

		else

		{
			wait(&statut);
			pid_t child_pid = wait(&statut);
			printf("staut is %d\n", child_pid);
		}
	}
	return (0);
}
