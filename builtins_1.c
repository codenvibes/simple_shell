#include "tsh.h"

/*
 * File - builtin_1.c
 * Auth: Terrence M.K & Tamara Lumumba
 * Decsription: This file contains the implementations of the 'history',
 *		and 'alias' commands.
 */

/**
 * tsh_history - prints the command history list
 * @data: pointer to a struct cmd_data containing the command history list
 *  Return: Always 0
 */
int tsh_history(cmd_data *data)
{
print_list(data->cmd_log);
return (0);
}

/**
 * unset_alias - sets alias to string
 * @data: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(cmd_data *data, char *str)
{
char *p, c;
int ret;

p = tsh_strchr(str, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = delete_node_at_index(&(data->tsh_alias),
get_node_index(data->tsh_alias, node_starts_with(data->tsh_alias, str, -1)));
*p = c;
return (ret);
}

/**
 * set_alias - sets alias to string
 * @data: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(cmd_data *data, char *str)
{
char *p;

p = tsh_strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (unset_alias(data, str));

unset_alias(data, str);
return (add_node_end(&(data->tsh_alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
char *p = NULL, *a = NULL;

if (node)
{
p = tsh_strchr(node->str, '=');
for (a = node->str; a <= p; a++)
tsh_putchar(*a);
tsh_putchar('\'');
tsh_puts(p + 1);
tsh_puts("'\n");
return (0);
}
return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(cmd_data *data)
{
int i = 0;
char *p = NULL;
list_t *node = NULL;

if (data->arg_count == 1)
{
node = data->tsh_alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; data->argv[i]; i++)
{
p = tsh_strchr(data->argv[i], '=');
if (p)
set_alias(data, data->argv[i]);
else
print_alias(node_starts_with(data->tsh_alias, data->argv[i], '='));
}

return (0);
}
