#ifndef LIBRARIES_H
#define LIBRARIES_H

/* Required Libraries for Simple Shell */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/* Prototypes used for Shell */

void working_directory(void);
void readline(char *incoming, char **args);
void shell_execute(char *cmd, char *command,
char **args, char **envp, char **av);

extern char **environ;

/* Variable Limitations */

#define BUFFER_SIZE 1024
#define MAX_LENGTH_OF_CMD 1024
#define MAX_LENGTH_OF_PARAMETERS 64

#endif
