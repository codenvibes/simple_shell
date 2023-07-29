#include "tsh.h"

/*
 * File - utilstr_1.c
 * Auth: Terrence M.K & Tamara Lumumba
 */

/**
 * tsh_strcpy - Copies the string pointed to by src to the buffer pointed to by dest.
 * @dest: The buffer where the copied string will be stored.
 * @src: The string to be copied.
 * Return: A pointer to the destination buffer after copying.
 * If src and dest are the same or src is NULL, the function returns dest without copying.
 */
char *tsh_strcpy(char *dest, char *src)
{
int i = 0;

if (dest == src || src == 0)
return (dest);
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = 0;
return (dest);
}

/**
 * tsh_strdup - returns a pointer to a newly allocated space in memory, which contains a copy of the string given as a parameter.
 * @str: pointer to the input string
 *
 * Return: pointer to the newly allocated space in memory, containing the copied string, or NULL if str is NULL or if memory allocation fails.
 */
char *tsh_strdup(const char *str)
{
int length = 0;
char *ret;

if (str == NULL)
return (NULL);
while (*str++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;
return (ret);
}

/**
 *tsh_puts - prints a string, followed by a new line
 *@str: pointer to the string to be printed
 *
 * Return: void
 */
void tsh_puts(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
tsh_putchar(str[i]);
i++;
}
}

/**
 * tsh_putchar - writes a character to the standard output
 * @c: the character to be written
 *
 * Return: On success, returns 1. On error, returns -1.
 */
int tsh_putchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}
