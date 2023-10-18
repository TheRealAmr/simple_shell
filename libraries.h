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

#include "functions.c"

/*void shell_exit(char *command, char *parameters[]);*/
void shell_getline(char *cmd, char **par);
void shell_execute(char *cmd, char *command,
	char **parameters, char **envp, char **av);

/* Variable Limitations */

#define MAX_LENGTH_OF_CMD 1024
#define MAX_LENGTH_OF_PARAMETERS 64

#endif
