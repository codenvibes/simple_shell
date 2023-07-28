#include "tsh.h"

/*
 * File: convert_aoi.c
 * Auth: Terrence M.K & Tamara Lumumba
 */

/**
 * tsh_interactive - If the shell is in interactive mode, it will return true.
 * @data: a pointer to an cmd_data struct containing shell information
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int tsh_interactive(cmd_data *data)
{
	return (isatty(STDIN_FILENO) && data->tsh_readfd <= 2);
}
