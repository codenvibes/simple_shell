#include "tsh.h"

/*
 * File - tsh_env.c
 * Auth: Terrence M.K & Tamara Lumumba
 */

/**
 * _myenv - prints the current environment
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(cmd_data *data)
{
print_list_str(data->tsh_env);
return (0);
}

/**
 * fetch_env - Function that gets the value of an environment variable.
 * @data: Pointer to a structure containing environment variables.
 * @name: Name of the environment variable to search for.
 *
 * Return: Pointer to the value of the environment variable if found,
 */
char *fetch_env(cmd_data *data, const char *name)
{
list_t *node = data->tsh_env;
char *p;

while (node)
{
p = match_prefix(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(cmd_data *data)
{
if (data->arg_count != 3)
{
err_str("Incorrect number of arguements\n");
return (1);
}
if (init_env(data, data->argv[1], data->argv[2]))
return (0);
return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(cmd_data *data)
{
int i;

if (data->arg_count == 1)
{
err_str("Too few arguements.\n");
return (1);
}
for (i = 1; i <= data->arg_count; i++)
_unsetenv(data, data->argv[i]);

return (0);
}

/**
 * populate_env_list - populates env linked list
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(cmd_data *data)
{
list_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
data->tsh_env = node;
return (0);
}
