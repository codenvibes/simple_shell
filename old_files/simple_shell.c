/*
 * File: simple_shell.c
 * Auth: Terrence M.K
 *	 Tamara Lumumba
 * Decsription: This file contains the main function, which serves as the
 *		entry point for the simple UNIX command line interpreter.
 *		It includes the necessary header files and defines the buffer
 *		size constant. The main function initializes the buffer, enters
 *		an infinite loop to read and execute commands, and frees allocated
 *		memory before exiting
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "prompt.h"
#include "command.h"

#define BUFFER_SIZE 1024

/**
 * main - Entry point for the simple UNIX command line interpreter
 *
 * Return: Always 0
 */
int main(void)
{
	char *buffer;
	size_t bufsize = BUFFER_SIZE;

	buffer = malloc(sizeof(char) * bufsize);
	if (buffer == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		ssize_t characters = read_command(&buffer, &bufsize);
		char **argv = tokenize_command(buffer);

		display_prompt();

		if (characters == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			else
			{
				perror("read_command");
				exit(EXIT_FAILURE);
			}
		}

		execute_command(argv);
		cleanup(buffer, argv);
	}

	free(buffer);
	exit(EXIT_SUCCESS);
}
