#include "libraries.h"

/**
 * main - shell copy program
 *
 * @ac: number of arguments
 * @av: arguments passed to the program
 * @envp: enviro var
 *
 * Return: 0
*/

int main(int ac, char **av, char **envp)
{
	int i;
	int exit_status;
	char command[MAX_LENGTH_OF_CMD];
	char *args[MAX_LENGTH_OF_PARAMETERS];
	int intermode = isatty(STDIN_FILENO);
	(void)ac;

	while (1)
	{
		if (intermode)
		{
			working_directory();
		}

		readline(command, args);

		if (strcmp(command, "exit") == 0)
		{
			exit_status = 0;
			if (args[1] != NULL)
			{
				exit_status = atoi(args[1]);
			}
			for (i = 0; args[i] != NULL; i++)
			{
				free(args[i]);
			}
			exit(exit_status);
		}

		if (strcmp(command, "env") == 0)
		{
			envcmd();
			for (i = 0; args[i] != NULL; i++)
			{
				free(args[i]);
			}
			continue;
		}

		exit_status = shell_execute(command, args, envp, av);

		for (i = 0; args[i] != NULL; i++)
		{
		  free(args[i]);
		}
	}

	return (exit_status);
}
