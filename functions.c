#include "libraries.h"

/***/

void envcmd(void)
{
	int x = 0;

	while (environ[x] != NULL)
	{
		printf("%s\n", environ[x]);
		x++;
	}
}

/**
 * readline - gets the input using getline() and separates
 *			it using the strtok() function then returns
 *
 * @incoming: command
 * @args: arguments/parameters of the command
 *
 * Return: command & arguments & 0 on failure
*/
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

void shell_execute(char *cmd, char *command,
	char **args, char **envp, char **av)
{
	int status;
	if (!isatty(STDOUT_FILENO))
	{
        perror("stdout is not a tty");
        exit(EXIT_FAILURE);
    }
	strcpy(cmd, "/bin/");
	strcat(cmd, command);
	if (fork() == 0)
	{
        execve(cmd, args, envp);
        fprintf(stderr, "%s: %s: %s\n", av[0], command, strerror(errno));
        exit(2);
    }
	else
	{
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            exit(WEXITSTATUS(status));
    }
}

/**
 * working_directory - prints the cisfun format followed by
 *					 the cwd and then the $ sign
 *
 * Return: void
*/
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
