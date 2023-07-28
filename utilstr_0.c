#include "tsh.h"

/*
 * File - utilstr_0.c
 * Auth: Terrence M.K & Tamara Lumumba
 */

/**
 * tsh_strlen - function that returns the length of a string
 * @s: the string to be measured
 *
 * Return: the length of the string
 */
int tsh_strlen(char *s)
{
int i = 0;

if (!s)
return (0);

while (*s++)
i++;
return (i);
}

/**
 * tsh_strcmp - Compares two strings lexicographically
 * @str1: Pointer to the first string to be compared
 * @str2: Pointer to the second string to be compared
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int tsh_strcmp(char *str1, char *str2)
{
while (*str1 && *str2)
{
if (*str1 != *str2)
return (*str1 - *str2);
str1++;
str2++;
}
if (*str1 == *str2)
return (0);
else
return (*str1 < *str2 ? -1 : 1);
}

/**
 * match_prefix - This function checks if the given haystack string starts with the given needle string.
 * @txt2search: The string to check.
 * @searchstr: needle The string to look for at the beginning of the haystack.
 *
 * Return: address of next char of haystack or NULL
 */
char *match_prefix(const char *txt2search, const char *searchstr)
{
while (*searchstr)
if (*searchstr++ != *txt2search++)
return (NULL);
return ((char *)txt2search);
}

/**
 * tsh_strcat - Concatenates the string pointed to by src to the end of the string pointed to by dest.
 * @dest: Pointer to the destination string where the concatenated string will be stored.
 * @src: Pointer to the source string that will be concatenated to the destination string.
 *
 * Return: Pointer to the beginning of the destination string.
 */
char *tsh_strcat(char *dest, char *src)
{
char *out = dest;

while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (out);
}
