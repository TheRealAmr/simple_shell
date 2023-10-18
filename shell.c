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
	char *args[MAX_LENGTH_OF_PARAMETERS];
	char *envp[] = { "PATH=/bin", NULL };
	(void)ac;

	while (1)
	{
		working_directory();
		readline(command, args);
		if (strcmp(command, "exit") == 0)
		{
			for (i = 0; args[i] != NULL; i++)
				free(args[i]);
			break;
		}
        envcmd(command);
		pid = fork();
		if (pid != 0)
			wait(NULL);
		else
			shell_execute(cmd, command, args, envp, av);

		/* Memory Leakage precautions */
		for (i = 0; args[i] != NULL; i++)
			free(args[i]);
	}
	return (0);
}
