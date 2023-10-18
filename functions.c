#include "libraries.h"

/*void shell_exit(char *command, char *parameters[])*/
/*{*/
/*    int i;*/

/*    if (strcmp(command, "exit") == 0)*/
/*    {*/
/*        for (i = 0; parameters[i] != NULL; i++)*/
/*            free(parameters[i]);*/
/*        //break;*/
/*    }*/
/*}*/
/* Cancelled the use of this function because I cannot use break */

/**
 * tokenize_input - takes the command from the user using getline()
 * @cmmd: searching for the path of the command itself
 * @par: arguments of the command such as -l or -lt
 * Return: 0
*/
int tokenize_input(char *cmmd, char *par[])
{
	int j;
	char *line = NULL;
	char *token = strtok(line, " \n");

	size_t line_length = 0;
	ssize_t read = getline(&line, &line_length, stdin);

	if (read == -1)
	{
		perror("getline");
		exit(1);
	}

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

	return (0);
}

/**
 * shellex - executes the program
 * @cmd: path
 * @command: the command itself
 * @parameters: the command arguments/args
 * @envp: the evironment of the command
 * @av: av[0] would only be used in case of an error
*/
void shellex(char *cmd, char *command,
	char **parameters, char **envp, char **av)
{
	strcpy(cmd, "/bin/");
	strcat(cmd, command);
	execve(cmd, parameters, envp);
	perror(av[0]);
	exit(1);
}
