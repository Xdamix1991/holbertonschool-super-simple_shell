#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/

split_string - split string in words
@line: string received
Description: count number of spaces, allow enought memory to
the double pointer, with strtok, copy the string in a static

variable in strtok and return a table of strings where every
case is a word
Return: the table of strings
*/
char split_string(char line)
{
	char **tokens;
	int count = 0;
	char token;

	for (int i = 0; line[i] != '\0'; i++)

	{
		if (line[i] == ' ')
		count++;
	}

	tokens = malloc((count + 2) * sizeof(char *));

	token = strtok(line, " ");
	for (int i = 0; token != NULL; i++)

	{
		tokens[i] = strdup(token);
		token = strtok(NULL, " ");
	}
	tokens[count + 1] = NULL;

	return (tokens);
}
/

main - read string entered by the user, split and print every words
Return: nothing
*/
int main(void)
{
	char *line = NULL;

	size_t len = 0;
	ssize_t nread;
	char tokens;

	while (1)
	{
		printf("$ ");
		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			break;
		}

		tokens = split_string(line);
		for (int i = 0; tokens[i] != NULL; i++)

		{
			if (i != 0)
				printf("\n");
			printf("%s", tokens[i]);
			free(tokens[i]);
		}
		free(tokens);
	}
	free(line);
	return (0);
}
