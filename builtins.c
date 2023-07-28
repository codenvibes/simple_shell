#include "tsh.h"

/*
 * File - builtin.c
 * Auth: Terrence M.K & Tamara Lumumba
 * Decsription: This file contains the implementations of the 'exit', 'cd',
 *		and 'help' commands
 */

/**
 * exit_cmd - Function to handle the 'exit' command in a command-line interface
 *	      Terminate the shell session.
 * @data: A pointer to a cmd_data struct containing the command-line arguments
 *  Return: (0) if data.argv[0] != "exit"
 */
int exit_cmd(cmd_data *data)
{
	int exitval;

	if (data->argv[1])  /* If there is an exit arguement */
	{
		exitval = error_atoi(data->argv[1]);
		if (exitval == -1)
		{
			data->status = 2;
			display_errmsg(data, "Undefined: ");
			err_str(data->argv[1]);
			err_char('\n');
			return (1);
		}
		data->err_num = error_atoi(data->argv[1]);
		return (-2);
	}
	data->err_num = -1;
	return (-2);
}

/**
 * cd_cmd - change directory command
 * @data: pointer to a cmd_data struct containing command information
 *  Return: Always 0
 */
int cd_cmd(cmd_data *data)
{
	char *cwd, *dir, buffer[1024];
	int cd_stat;

	cwd = getcwd(buffer, 1024);
	if (!cwd)
		tsh_puts(">>Failed to fetch current directory<<\n");
	if (!data->argv[1])
	{
		dir = fetchenv(data, "HOME=");
		if (!dir)
			cd_stat =
				chdir((dir = fetchenv(data, "PWD=")) ? dir : "/");
		else
			cd_stat = chdir(dir);
	}
	else if (tsh_strcmp(data->argv[1], "-") == 0)
	{
		if (!fetchenv(data, "OLDPWD="))
		{
			tsh_puts(cwd);
			tsh_putchar('\n');
			return (1);
		}
		tsh_puts(fetchenv(data, "OLDPWD=")), tsh_putchar('\n');
		cd_stat =
			chdir((dir = fetchenv(data, "OLDPWD=")) ? dir : "/");
	}
	else
		cd_stat = chdir(data->argv[1]);
	if (cd_stat == -1)
	{
		display_errmsg(data, "can't cd to ");
		err_str(data->argv[1]), err_char('\n');
	}
	else
	{
		init_env(data, "OLDPWD", fetchenv(data, "PWD="));
		init_env(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * cd_help - Displays the help message
 * @data: pointer to a cmd_data struct containing command information
 *  Return: Always 0
 */
int cd_help(cmd_data *data)
{
	char **arg_array;

	arg_array = data->argv;
	tsh_puts("The 'help' command is not fully implemented yet. \n");
	if (0)
		tsh_puts(*arg_array);
	return (0);
}
