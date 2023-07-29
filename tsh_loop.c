#include "tsh.h"

/*
 * File - tsh_loop.c
 * Auth: Terrence M.K & Tamara Lumumba
 * Decsription: This file contains the main shell loop, as well as functions
 *		for finding built-in commands and external commands in the
 *		PATH, and for forking a new process to run external commands.
 */

/**
 * run_loop - main shell loop
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
		if (tsh_interact(data))
			tsh_puts("$ ");
		err_char(BUF_FLUSH);
		value = get_input(data);
		if (value != -1)
		{
			set_data(data, av);
			cmd_res = search_run(data);
			if (cmd_res == -1)
				check_path(data);
		}
		else if (tsh_interact(data))
			tsh_putchar('\n');
		free_data(data, 0);
	}
	write_history(data);
	free_data(data, 1);
	if (!tsh_interact(data) && data->tsh_status)
		exit(data->tsh_status);
	if (cmd_res == -2)
	{
		if (data->xcode == -1)
			exit(data->tsh_status);
		exit(data->xcode);
	}
	return (cmd_res);
}

/**
 * search_run - Finds and executes the appropriate built-in command
 * @data: Pointer to the cmd_data struct containing information about the
 *	  command to be executed.
 * Return: -1 if builtin not found,
 *                     0 if builtin executed successfully,
 *                     1 if builtin found but not successful,
 *                     -2 if builtin signals exit()
 */
int search_run(cmd_data *data)
{
	int x, retval = -1;
	builtin_reg builtin_entry[] = {
		{"exit", exit_cmd},
		{"env", _myenv},
		{"help", cd_help},
		{"history", tsh_history},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", cd_cmd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; builtin_entry[x].type; x++)
		if (tsh_strcmp(data->argv[0], builtin_entry[x].type) == 0)
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
 *
 * Return: void
 */
void check_path(cmd_data *data)
{
	char *course = NULL;
	int x, t;

	data->course = data->argv[0];
	if (data->line_count == 1)
	{
		data->index++;
		data->line_count = 0;
	}
	for (x = 0, t = 0; data->arg[x]; x++)
		if (!tsh_delim(data->arg[x], " \t\n"))
			t++;
	if (!t)
		return;

	course = abs_path(data, fetch_env(data, "PATH="), data->argv[0]);
	if (course)
	{
		data->course = course;
		tsh_fork(data);
	}
	else
	{
		if ((tsh_interact(data) || fetch_env(data, "PATH=")
					|| data->argv[0][0] == '/') && valid_exe(data, data->argv[0]))
			tsh_fork(data);
		else if (*(data->arg) != '\n')
		{
			data->tsh_status = 127;
			diplay_error(data, "not found\n");
		}
	}
}

/**
 * tsh_fork - Creates a child process using fork() and executes a command in it
 * @data: A pointer to a struct containing information about the command to be
 *	  executed
 *
 * Return: void
 */
void tsh_fork(cmd_data *data)
{
	pid_t cpid;

	cpid = fork();
	if (cpid == -1)
	{
		perror("Error:");
		return;
	}
	if (cpid == 0)
	{
		if (execve(data->course, data->argv, get_environ(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->tsh_status));
		if (WIFEXITED(data->tsh_status))
		{
			data->tsh_status = WEXITSTATUS(data->tsh_status);
			if (data->tsh_status == 126)
				diplay_error(data, "Permission denied\n");
		}
	}
}
