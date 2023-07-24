#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

/*
 * File: command.c
 * Auth: Terrence M.K
 */

ssize_t read_command(char **buffer, size_t *bufsize);
char **tokenize_command(char *buffer);
void execute_command(char **argv);
void cleanup(char *buffer, char **argv);

#endif /* COMMAND_H */
