#include "tsh.h"

/*
 * File - fetch_env.c
 * Auth: Terrence M.K & Tamara Lumumba
 */

/**
 * get_environ - returns the string array copy of our environ
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(cmd_data *data)
{
if (!data->environ || data->env_changed)
{
data->environ = list_to_strings(data->tsh_env);
data->env_changed = 0;
}

return (data->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(cmd_data *data, char *var)
{
list_t *node = data->tsh_env;
size_t i = 0;
char *p;

if (!node || !var)
return (0);

while (node)
{
p = match_prefix(node->str, var);
if (p && *p == '=')
{
data->env_changed = delete_node_at_index(&(data->tsh_env), i);
i = 0;
node = data->tsh_env;
continue;
}
node = node->next;
i++;
}
return (data->env_changed);
}

/**
 * init_env - Sets an environment variable with the given name and value
 * @data: A pointer to the cmd_data struct containing environment variables
 * @var: The name of the environment variable to set
 * @value: The value to set for the environment variable
 *  Return: 0 on success, 1 on failure
 */
int init_env(cmd_data *data, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *p;

if (!var || !value)
return (0);

buf = malloc(tsh_strlen(var) + tsh_strlen(value) + 2);
if (!buf)
return (1);
tsh_strcpy(buf, var);
tsh_strcat(buf, "=");
tsh_strcat(buf, value);
node = data->tsh_env;
while (node)
{
p = match_prefix(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
data->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_end(&(data->tsh_env), buf, 0);
free(buf);
data->env_changed = 1;
return (0);
}
