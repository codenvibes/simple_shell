#include "tsh.h"

/*
 * File - tsh.c
 * Auth: Terrence M.K & Tamara Lumumba
 */

/**
 * main - entry point of the program.
 * @ac: number of command line arguments.
 * @av: array of pointers to command line arguments
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
cmd_data data[] = { INFO_INIT };
int fd = 2;

asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (fd)
: "r" (fd));

if (ac == 2)
{
fd = open(av[1], O_RDONLY);
if (fd == -1)
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
data->readfd = fd;
}
populate_env_list(data);
read_history(data);
run_loop(data, av);
return (EXIT_SUCCESS);
}
