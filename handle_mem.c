#include "tsh.h"

/*
 * File - handle_mem.c
 * Auth: Terrence M.K & Tamara Lumumba
 */

/**
 * tsh_dealloc - Frees the memory pointed to by a pointer and sets the pointer to NULL.
 * @ptr: A pointer to a pointer to the memory to be freed.
 *
 * Return: 1 if memory was successfully freed, 0 otherwise.
 */
int tsh_dealloc(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}
