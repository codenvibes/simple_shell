#include "tsh.h"

/*
 * File - builtin.c
 * Auth: Terrence M.K & Tamara Lumumba
 */

/**
 * error_atoi - Converts a string representation of an integer to an actual
 *		integer value.
 * @str: A pointer to the string that needs to be converted to an integer.
 * Return: the integer value of the string if successful, otherwise returns -1.
 */
int error_atoi(char *str)
{
	int index = 0;
	unsigned long int retval = 0;

	if (*str == '+')
		str++;
	for (index = 0;  str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			retval *= 10;
			retval += (str[index] - '0');
			if (retval > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (retval);
}

/**
 * display_errmsg - Displays an error message to the standard error stream.
 * @data: Pointer to the cmd_data struct containing command data.
 * @estr: Pointer to the error message string to be displayed.
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void display_errmsg(cmd_data *data, char *estr)
{
	err_str(data->fname);
	err_str(": ");
	print_d(data->index, STDERR_FILENO);
	err_str(": ");
	err_str(data->argv[0]);
	err_str(": ");
	err_str(estr);
}

/**
 *err_str - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void err_str(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		err_char(str[i]);
		i++;
	}
}

/**
 * err_char - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int err_char(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}