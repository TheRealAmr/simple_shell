#include "libraries.h"

/**
 * main - shell copy program
 *
 * @ac: number of arguments
 * @av: arguments passed to the program
 *
 * Return: 0
*/

int main(int ac, char **av, char **envp)
{
	int i;
	int pid;
	int exit_status;
	char cmd[MAX_LENGTH_OF_CMD];
	char command[MAX_LENGTH_OF_CMD];
	char *args[MAX_LENGTH_OF_PARAMETERS];
	int intermode = isatty(STDIN_FILENO);
	(void)ac;

	while (1)
	{
		if (intermode)
            working_directory();
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
			continue;
		}
		pid = fork();
		if (pid != 0)
			wait(NULL);
		else
		{
			if (!isatty(STDIN_FILENO))
				dup2(STDOUT_FILENO, STDIN_FILENO);
			if (!isatty(STDOUT_FILENO))
				dup2(STDIN_FILENO, STDOUT_FILENO);
			if (!isatty(STDERR_FILENO))
				dup2(STDIN_FILENO, STDERR_FILENO);
			shell_execute(cmd, command, args, envp, av);
		}
		/* Memory Leakage precautions */
		for (i = 0; args[i] != NULL; i++)
			free(args[i]);
	}
	return (0);
}
