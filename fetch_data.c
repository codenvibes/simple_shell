#include "tsh.h"

/*
 * File - fetch_data.c
 * Auth: Terrence M.K & Tamara Lumumba
 */

/**
 * clear_data - initializes cmd_data struct
 * @data: struct address
 */
void clear_data(cmd_data *data)
{
data->arg = NULL;
data->argv = NULL;
data->course = NULL;
data->arg_count = 0;
}

/**
 * set_data - Sets the data for the cmd_data struct based on the provided arguments.
 * @data: Pointer to the cmd_data struct to be populated.
 * @av: Array of strings containing the command arguments.
 */
void set_data(cmd_data *data, char **av)
{
int i = 0;

data->filename = av[0];
if (data->arg)
{
data->argv = strtow(data->arg, " \t");
if (!data->argv)
{

data->argv = malloc(sizeof(char *) * 2);
if (data->argv)
{
data->argv[0] = tsh_strdup(data->arg);
data->argv[1] = NULL;
}
}
for (i = 0; data->argv && data->argv[i]; i++)
;
data->arg_count = i;

tsh_replace_alias(data);
tsh_replace_vars(data);
}
}

/**
 * free_data - Frees the memory allocated for cmd_data struct.
 * @data: pointer to the cmd_data struct
 * @all: flag to indicate if all memory should be freed
 */
void free_data(cmd_data *data, int all)
{
ffree(data->argv);
data->argv = NULL;
data->course = NULL;
if (all)
{
if (!data->cmd_buf)
free(data->arg);
if (data->tsh_env)
tsh_free_list(&(data->tsh_env));
if (data->cmd_log)
tsh_free_list(&(data->cmd_log));
if (data->tsh_alias)
tsh_free_list(&(data->tsh_alias));
ffree(data->environ);
data->environ = NULL;
tsh_dealloc((void **)data->cmd_buf);
if (data->readfd > 2)
close(data->readfd);
tsh_putchar(BUF_FLUSH);
}
}
