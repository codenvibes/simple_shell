#include "tsh.h" /* Include main header file */

/* List of builtin commands, followed by their corresponding functions */
char *builtin_str[] = {
	"cd",
	"help",
	"exit"
};

int (*builtin_func[]) (char **) = {
	&tsh_cd,
	&tsh_help,
	&tsh_exit
};

/**
 * tsh_loop - Main loop of the shell.
 * Reads input from the user, parses it into commands, and executes them.
 */
void tsh_loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf("> ");
		line = tsh_read_line();
		args = tsh_split_line(line);
		status = tsh_execute(args);
		free(line);
		free(args);
	} while (status);
}

/**
 * main - Main entry point.
 * @argc: Argument count.
 * @argv: Argument vector.
 * Return: status code
 */
int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	/*Load config files, if any.*/

	/*Run command loop.*/
	tsh_loop();

	/*Perform any shutdown/cleanup.*/
	return (EXIT_SUCCESS);
}
