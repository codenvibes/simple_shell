#include "tsh.h"

/*
 * File - tsh.c
 * Auth: Terrence M.K & Tamara Lumumba
 */

/**
 * main - The main function of the program
 * @ac: arg count
 * @av: arg vector
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	cmd_data data[] = { INFO_INIT };
	int tsh_fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (tsh_fd)
		: "r" (tsh_fd));

	if (ac == 2)
	{
		tsh_fd = open(av[1], O_RDONLY);
		if (tsh_fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				err_str(av[0]);
				err_str(": 0: Can't open ");
				err_str(av[1]);
				err_char('\n');
				err_char(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->tsh_readfd = tsh_fd;
	}
	populate_env_list(data);
	read_history(data);
	run_loop(data, av);
	return (EXIT_SUCCESS);
}
