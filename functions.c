#include "libraries.h"

/**
 * find_command_in_path - looks for command in path
 *
 * @command: the command variable
 *
 * Return: NULL
*/
char *find_command_in_path(char *command)
{
	char *PATH = strdup(getenv("PATH"));
	char *path = strtok(PATH, ":");
	static char full_command[1024];

	while (path != NULL)
	{
		DIR *dir = opendir(path);
		struct dirent *entry;

		if (dir)
		{
			while ((entry = readdir(dir)) != NULL)
			{
				if (strcmp(entry->d_name, command) == 0)
				{
					snprintf(full_command, sizeof(full_command), "%s/%s", path, command);
					closedir(dir);
					free(PATH);
					return (full_command);
				}
			}
			closedir(dir);
		}

		path = strtok(NULL, ":");
	}
	free(PATH);
	return (NULL);
}

/**
 * envcmd - environ command
 * Return: void
*/
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
	char *comment_pos;
	size_t length = 0;
	ssize_t input = getline(&inc, &length, stdin);

	if (input == -1)
	{
		perror("Error");
		free(inc);
		exit(EXIT_FAILURE);
	}

	comment_pos = strchr(inc, '#');
	if (comment_pos)
	{
		*comment_pos = '\0';
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

/**
 * shell_execute - executes the commands
 *
 * @command: the command
 * @args: command args
 * @envp: command enviro
 * @av: av[0]
 *
 * Return: void
*/
void shell_execute(char *command, char **args, char **envp, char **av)
{
	int status;
	char *full_path_command;

	if (!isatty(STDOUT_FILENO))
	{
		perror("stdout is not a tty");
		exit(EXIT_FAILURE);
	}

	if (strchr(command, '/'))
	{
		full_path_command = strdup(command);
	}
	else
	{
		full_path_command = find_command_in_path(command);
	}

	if (full_path_command)
	{
		if (fork() == 0)
		{
			execve(full_path_command, args, envp);
			fprintf(stderr, "%s: %s: %s\n", av[0], command, strerror(errno));
			exit(2);
		}
		else
		{
			wait(&status);
			/*free(full_path_command);*/
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
				exit(WEXITSTATUS(status));
		}
	}
	else
	{
		fprintf(stderr, "%s: %s: command not found\n", av[0], command);
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
