#include "tsh.h"

/*
 * File - convert_atoi.c
 * Auth: Terrence M.K & Tamara Lumumba
 */


/**
 * tsh_interact - Checks if the current process is interacting with a terminal
 * @data: a pointer to the cmd_data struct that holds information about the
 *	  command being executed
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int tsh_interact(cmd_data *data)
{
	return (isatty(STDIN_FILENO) && data->readfd <= 2);
}

/**
 * tsh_delim - checks if character is a delimeter
 * @c: the character to be checked
 * @delim:the string of delimiters to compare with
 * Return: 1 if true, 0 if false
 */
int tsh_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *tsh_isalpha - Checks if the input character is an alphabet character.
 *@k: The character to be checked.
 *Return: 1 if the character is an alphabet character, 0 otherwise.
 */

int tsh_isalpha(int k)
{
if ((k >= 'a' && k <= 'z') || (k >= 'A' && k <= 'Z'))
return (1);
else
return (0);
}

/**
 *tsh_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int tsh_atoi(char *s)
{
int a, sign = 1, flag = 0, output;
unsigned int result = 0;

for (a = 0;  s[a] != '\0' && flag != 2; a++)
{
if (s[a] == '-')
sign *= -1;

if (s[a] >= '0' && s[a] <= '9')
{
flag = 1;
result *= 10;
result += (s[a] - '0');
}
else if (flag == 1)
flag = 2;
}

if (sign == -1)
output = -result;
else
output = result;

return (output);
}
