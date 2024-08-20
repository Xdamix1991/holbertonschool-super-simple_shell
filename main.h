#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;
#define MAX_ARGUMENTS 10
#define MAX_COMMAND_LENGTH 1024


char *find_command_path(const char *command);
char *my_getenv(const char *name);
void free_argv(char **argv);
char **split_string(int max_argument);
int execute_command(int max_argument, char **envp);

#endif
