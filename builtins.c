#include "tsh.h" /* Include main header file */

/* Builtin function Declarations: */

/**
 * tsh_cd - Change directory.
 * Changes the current working directory to the specified path.
 * If no path is provided, an error message is displayed.
 * @args: An array of strings representing the command and its arguments.
 * Return: 1 if the command is executed successfully, otherwise 0.
 */
int tsh_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "tsh: expected argument to \"cd\"\n");
	} else
	{
		if (chdir(args[1]) != 0)
		{
			perror("tsh");
		}
	}
	return (1);
}

/**
 * tsh_help - Display help information about the shell.
 * Displays information about the built-in commands and how to use the shell.
 * @args: An array of strings representing the command and its arguments.
 * Return: 1 if the command is executed successfully, otherwise 0.
 */
int tsh_help(char **args __attribute__((unused)))
{
	int i;

	printf("Terrence's & Tamara's tsh\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");

	for (i = 0; i < tsh_num_builtins(); i++)
	{
		printf("  %s\n", builtin_str[i]);
	}
	printf("Use the man command for information on other programs.\n");
	return (1);
}

/**
 * tsh_exit - Exit the shell.
 * Exits the shell program.
 * @args: An array of strings representing the command and its arguments.
 * Return: 0 to indicate the shell should terminate.
 */
int tsh_exit(char **args __attribute__((unused)))
{
	return (0);
}