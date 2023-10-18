#include "libraries.h"

/**
 * main - shell copy program
 *
 * @ac: number of arguments
 * @av: arguments passed to the program
 *
 * Return: 0
*/

int main(int ac, char **av)
{
	int i;
	int pid;
	char cmd[MAX_LENGTH_OF_CMD];
	char command[MAX_LENGTH_OF_CMD];
	char *parameters[MAX_LENGTH_OF_PARAMETERS];
	char *envp[] = { "PATH=/bin", NULL };
	(void)ac;

	while (1)
	{
		printf("$ ");
		tokenize_input(command, parameters);
		if (strcmp(command, "exit") == 0)
		{
			for (i = 0; parameters[i] != NULL; i++)
				free(parameters[i]);

			break;
		}
		pid = fork();
		if (pid != 0)
			wait(NULL);
		else
			shellex(cmd, command, parameters, envp, av);
		/* Memory Leakage precautions */
		for (i = 0; parameters[i] != NULL; i++)
			free(parameters[i]);
	}
	return (0);
}
