#include "tsh.h"

/*
 * File - builtin_0.c
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
data->tsh_status = 2;
diplay_error(data, "Illegal number: ");
err_str(data->argv[1]);
err_char('\n');
return (1);
}
data->xcode = error_atoi(data->argv[1]);
return (-2);
}
data->xcode = -1;
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
dir = fetch_env(data, "HOME=");
if (!dir)
cd_stat = /* TODO: what should this be? */
chdir((dir = fetch_env(data, "PWD=")) ? dir : "/");
else
cd_stat = chdir(dir);
}
else if (tsh_strcmp(data->argv[1], "-") == 0)
{
if (!fetch_env(data, "OLDPWD="))
{
tsh_puts(cwd);
tsh_putchar('\n');
return (1);
}
tsh_puts(fetch_env(data, "OLDPWD=")), tsh_putchar('\n');
cd_stat = /* TODO: what should this be? */
chdir((dir = fetch_env(data, "OLDPWD=")) ? dir : "/");
}
else
cd_stat = chdir(data->argv[1]);
if (cd_stat == -1)
{
diplay_error(data, "can't cd to ");
err_str(data->argv[1]), err_char('\n');
}
else
{
init_env(data, "OLDPWD", fetch_env(data, "PWD="));
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
tsh_puts(*arg_array); /* temp att_unused workaround */
return (0);
}
