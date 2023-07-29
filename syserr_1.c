#include "tsh.h"

/*
 * File - sys_error_1.c
 * Auth: Terrence M.K & Tamara Lumumba
 */

/**
 * error_atoi - Converts a string representation of an integer to an integer value.
 * @s: The string representation of the integer to be converted.
 * Return: The integer value of the input string, or -1 if the string is invalid.
 */
int error_atoi(char *s)
{
int i = 0;
unsigned long int result = 0;

if (*s == '+')
s++;
for (i = 0;  s[i] != '\0'; i++)
{
if (s[i] >= '0' && s[i] <= '9')
{
result *= 10;
result += (s[i] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
}
return (result);
}

/**
 * diplay_error - print an error message to the standard error stream.
 * @data: a pointer to a cmd_data struct representing the command data
 * @estr: a pointer to a char array representing the error message to be printed
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void diplay_error(cmd_data *data, char *estr)
{
err_str(data->filename);
err_str(": ");
print_d(data->index, STDERR_FILENO);
err_str(": ");
err_str(data->argv[0]);
err_str(": ");
err_str(estr);
}

/*
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
int (*__putchar)(char) = tsh_putchar;
int i, count = 0;
unsigned int _abs_, current;

if (fd == STDERR_FILENO)
__putchar = err_char;
if (input < 0)
{
_abs_ = -input;
__putchar('-');
count++;
}
else
_abs_ = input;
current = _abs_;
for (i = 1000000000; i > 1; i /= 10)
{
if (_abs_ / i)
{
__putchar('0' + current / i);
count++;
}
current %= i;
}
__putchar('0' + current);
count++;

return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
static char *array;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = num;

if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';

}
array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';

do      {
*--ptr = array[n % base];
n /= base;
} while (n != 0);

if (sign)
*--ptr = sign;
return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
int i;

for (i = 0; buf[i] != '\0'; i++)
if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
buf[i] = '\0';
break;
}
}
