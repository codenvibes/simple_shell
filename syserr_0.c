#include "tsh.h"

/*
 * File - sys_error_0.c
 * Auth: Terrence M.K & Tamara Lumumba
 */

/**
 * err_str - Prints the characters in the given string to the standard error
 *	     output.
 * @str: The input string to print.
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
 * err_char - write a character to the standard error output
 * @c: The character to be written to the standard error output.
 *
 * Return: Returns 1 if successful, otherwise returns an error code.
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

/**
 * write_fd - writes a character to a file descriptor buffer
 * @c: the character to be written
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_fd(char c, int fd)
{
static int z;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || z >= WRITE_BUF_SIZE)
{
write(fd, buf, z);
z = 0;
}
if (c != BUF_FLUSH)
buf[z++] = c;
return (1);
}

/**
 *_putsfd - writes a string to a file descriptor
 * @str: pointer to the string to be written
 * @fd: file descriptor to write the string to
 *
 * Return: the number of characters written, or 0 if the input string is NULL
 */
int _putsfd(char *str, int fd)
{
int b = 0;

if (!str)
return (0);
while (*str)
{
b += write_fd(*str++, fd);
}
return (b);
}
