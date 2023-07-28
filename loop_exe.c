#include "tsh.h"
/*
 * File - loop_exec.c
 * Auth: Terrence M.K & Tamara Lumumba
 * Decsription: This file contains the main shell loop, as well as functions
 *		for finding built-in commands and external commands in the
 *		PATH, and for forking a new process to run external commands.
 */

/**
 * run_loop - Main shell loop
 * @data: a pointer to an cmd_data struct containing shell information
 * @av: double pointer to an array of strings containing command line arguments
 *
 * Return: 0 on success, 1 on error, or error code
 */
int run_loop(cmd_data *data, char **av)
{
	ssize_t value = 0;
	int cmd_res = 0;

	while (value != -1 && cmd_res != -2)
	{
		clear_data(data);
		if (interactive(data))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		value = get_input(data);
		if (value != -1)
		{
			set_data(data, av);
			cmd_res = search_run(data);
			if (cmd_res == -1)
				check_path(data);
		}
		else if (interactive(data))
			_putchar('\n');
		free_data(data, 0);
	}
	write_history(data);
	free_data(data, 1);
	if (!interactive(data) && data->status)
		exit(data->status);
	if (cmd_res == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}
	return (cmd_res);
}

/**
 * search_run - Finds and executes the appropriate built-in command
 * @data: Pointer to the cmd_data struct containing information about the
 *	  command to be executed.
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int search_run(cmd_data *data)
{
	int x, retval = -1;
	builtin_reg builtin_entry[] = {
		{"exit", _myexit},
		{"help", _myhelp},
		{"cd", _mycd},
		{NULL, NULL}
	};

	/* Loop through the array to find the appropriate built-in command */
	for (x = 0; builtin_entry[x].type; x++)
		if (_strcmp(data->argv[0], builtin_entry[x].type) == 0)
		{
			data->index++;
			retval = builtin_entry[x].func(data);
			break;
		}
	return (retval);
}

/**
 * check_path - searches for a command in PATH
 * @data: Pointer to the command data struct
 * Return: void
 */
void check_path(cmd_data *data)
{
	char *path = NULL;
	int x, delim;

	data->path = data->argv[0];
	if (data->linecount == 1)
	{
		data->index++;
		data->linecount = 0;
	}
	for (x = 0, delim = 0; data->arg[x]; x++)
		if (!is_delim(data->arg[x], " \t\n"))
			delim++;
	if (!delim)
		return;

	path = find_path(data, _getenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		fork_run(data);
	}
	else
	{
		if (interactive(data) || _getenv(data, "PATH=")
		|| data->argv[0][0] == '/')
		{
			if (is_cmd(data, data->argv[0]))
			{
				fork_run(data);
				}
				else if (*(data->arg) != '\n')
				{
					data->status = 127;
				}
		}
	}
}