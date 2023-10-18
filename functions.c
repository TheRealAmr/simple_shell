#include "libraries.h"

void readline(char *incoming, char **args)
{
	int k = 0;
	char *token;
	char *inc = NULL;
	size_t length = 0;
	ssize_t input = getline(&inc, &length, stdin);

	if (input == -1)
	{
		perror("Error");
		free(inc);
		exit(EXIT_FAILURE);
	}

	token = strtok(inc, " \n");
	while (token != NULL)
	{
		args[k] = strdup(token);
		token = strtok(NULL, " \n");
		k++;
	}

	args[k] = NULL;

	if (k > 0)
	{
	strcpy(incoming, args[0]);
	}

	free(inc);
}

void shell_getline(char *cmmd, char *par[])
{
	int j;
	int z;
	char *line = NULL;
	char *token = NULL;
	size_t line_length = 0;
	ssize_t read = getline(&line, &line_length, stdin);

	if (read == -1)
	{
		perror("getline");
		free(line);
		exit(1);
	}
	token = strtok(line, " \n");
	j = 0;
	while (token != NULL)
	{
		par[j] = strdup(token);
		token = strtok(NULL, " \n");
		j++;
	}

	par[j] = NULL;

	if (j > 0)
		strcpy(cmmd, par[j]);

	free(line);
	for (z = 0; z < j; z++)
	free(par[z]);
}

/**
 * shellex - executes the program
 * @cmd: path
 * @command: the command itself
 * @args: the command arguments/args
 * @envp: the evironment of the command
 * @av: av[0] would only be used in case of an error
*/
void shell_execute(char *cmd, char *command,
	char **args, char **envp, char **av)
{
	strcpy(cmd, "/bin/");
	strcat(cmd, command);
	execve(cmd, args, envp);
	perror(av[0]);
	exit(EXIT_FAILURE);
}

void working_directory(void)
{
	size_t size = BUFFER_SIZE;
	char *buff = (char *)malloc(size);

	if (buff == NULL)
	{
		perror("Error");
		free(buff);
		exit(EXIT_FAILURE);
	}

	while (getcwd(buff, size) == NULL)
	{
		size = size * 2;
		buff = (char *)realloc(buff, size);
		if (buff == NULL)
		{
			perror("Error");
			free(buff);
			exit(EXIT_FAILURE);
		}
	}

	printf("#cisfun%s$ ", buff);
	free(buff);
}
