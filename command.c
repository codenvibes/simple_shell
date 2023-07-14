/*
 * File: command.c
 * Auth: Terrence M.K
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "command.h"

#define TOKEN_DELIMITERS " \t\n\r\a"

/**
 * read_command - Reads the command entered by the user
 * @buffer: Pointer to the command buffer
 * @bufsize: Pointer to the buffer size
 * Return: The number of characters read, or -1 on failure
 */
ssize_t read_command(char **buffer, size_t *bufsize)
{
	return (getline(buffer, bufsize, stdin));
}

/**
 * tokenize_command - Tokenizes the command into arguments
 * @buffer: Pointer to the command buffer
 *
 * Return: Double pointer to the array of arguments (argv)
 */
char **tokenize_command(char *buffer)
{
	char **argv = malloc(sizeof(char *) * BUFFER_SIZE);
	int argc = 0;
	char *token = strtok(buffer, TOKEN_DELIMITERS);

	if (argv == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	while (token != NULL && argc < BUFFER_SIZE - 1)
	{
		argv[argc] = token;
		argc++;
		token = strtok(NULL, TOKEN_DELIMITERS);
	}
	argv[argc] = NULL;

	return (argv);
}

/**
 * execute_command - Executes the command with the provided arguments
 * @argv: Array containing the command and arguments
 */
void execute_command(char **argv)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execvp(argv[0], argv) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}

/**
 * cleanup - Cleans up allocated resources and resets variables
 * @buffer: Pointer to the command buffer
 * @argv: Array containing the command and arguments
 */
void cleanup(char *buffer, char **argv)
{
	memset(buffer, 0, strlen(buffer));
	free(argv);
}
