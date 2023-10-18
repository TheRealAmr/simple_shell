#ifndef LIBRARIES_H
#define LIBRARIES_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "functions.c"

void getline();
void shellexecute();

#define MAX_LENGTH_OF_CMD 1024
#define MAX_LENGTH_OF_PARAMETERS 64

#endif
