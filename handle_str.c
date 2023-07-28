#include "tsh.h"

/*
 * File - handle_str.c
 * Auth: Terrence M.K & Tamara Lumumba
 */

/**
 **cpy_str - copies a string up to n characters from source to destination
 *@dest: pointer to the destination buffer
 *@src: pointer to the source string
 *@n: number of characters to copy
 *Return: pointer to the destination buffer
 */
char *cpy_str(char *dest, char *src, int n)
{
int i, o;
char *s = dest;

i = 0;
while (src[i] != '\0' && i < n - 1)
{
dest[i] = src[i];
i++;
}
if (i < n)
{
o = i;
while (o < n)
{
dest[o] = '\0';
o++;
}
}
return (s);
}

/**
 * *tsh_strncat - Concatenates two strings up to a specified number of
 *		  characters from the source string.
 * @dest: pointer to the destination string where the concatenated result
 *	  will be stored
 * @src: pointer to the source string that will be concatenated to the
 *	 destination string
 * @d: maximum number of characters to be concatenated from the source string
 * Return: pointer to the destination string containing the concatenated result
 */
char *tsh_strncat(char *dest, char *src, int d)
{
int i, j;
char *s = dest;

i = 0;
j = 0;
while (dest[i] != '\0')
i++;
while (src[j] != '\0' && j < d)
{
dest[i] = src[j];
i++;
j++;
}
if (j < d)
dest[i] = '\0';
return (s);
}

/**
 ** tsh_strchr - searches for the first occurrence of a character in a string.
 * @s: the string to search through.
 * @c: the character to find.
 * Return: a pointer to the first occurrence of the character c in the string
 *	   s, or NULL if the character is not found.
 */
char *tsh_strchr(char *s, char c)
{
do {
/*If the current character in the string is equal to c return a pointer to it*/
if (*s == c)
return (s);
} while (*s++ != '\0');

return (NULL);
}
