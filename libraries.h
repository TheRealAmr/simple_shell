#ifndef LIBRARIES_H
#define LIBRARIES_H

/* Required Libraries for Simple Shell */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

/* Prototypes used for Shell */

void working_directory(void);
void envcmd(void);
void readline(char *incoming, char **args);
void shell_execute(char *command, char **args,
char **envp, char **av);
char *find_command_in_path(char *command);

extern char **environ;

/* Variable Limitations */

#define BUFFER_SIZE 1024
#define MAX_LENGTH_OF_CMD 1024
#define MAX_LENGTH_OF_PARAMETERS 64

#endif
