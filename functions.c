#include "libraries.h"

/**
 * shell_getline - takes the command from the user using getline()
 * @cmd: searching for the path of the command itself
 * @par: arguments of the command such as -l or -lt
*/

void shell_getline(char *cmd, char **par)
{
	int i = 0;
	char *line = NULL;
	char *token = strtok(line, " \n");

	size_t line_length = 0;
	ssize_t read = getline(&line, &line_length, stdin);

	if (read == -1)
	{
	perror("getline");
	exit(1);
	}

	while (token != NULL)
	{
	par[i] = strdup(token);
	token = strtok(NULL, " \n");
	i++;
	}

	par[i] = NULL;

	if (i > 0)
	strcpy(cmd, par[0]);

	free(line);
}

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
