#include "tsh.h" /* Include main header file */

/* Utility function implementations */

/**
 * tsh_num_builtins - Get the number of built-in commands.
 * Return: The number of built-in commands.
 */

int tsh_num_builtins(void)
{
	extern size_t sizeof_builtin_str;

	return (sizeof_builtin_str);
}

/**
 * tsh_launch - Launch an external program.
 * Forks a child process to execute the specified program with arguments.
 * The parent process waits for the child to finish before returning.
 * @args: An array of strings representing the command and its arguments.
 * Return: 1 if the command is executed successfully, otherwise 0.
 */
int tsh_launch(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		/*Child process*/
		if (execvp(args[0], args) == -1)
		{
			perror("tsh");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		/*Error forking*/
		perror("tsh");
	}
	else
	{
		/*Parent process*/
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}

/**
 * tsh_execute - Execute a shell command.
 * Checks if the command is a built-in command and executes it if possible,
 * otherwise launches an external program.
 * @args: An array of strings representing the command and its arguments.
 * Return: 1 if the command is executed successfully, otherwise 0.
 */
int tsh_execute(char **args)
{
	int i;

	if (args[0] == NULL)
	{
		/*An empty command was entered.*/
		return (1);
	}

	for (i = 0; i < tsh_num_builtins(); i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
		{
			return ((*builtin_func[i])(args));
		}
	}

	return (tsh_launch(args));
}

/**
 * tsh_read_line - Read a line of input from the user.
 * Allocates memory for the line and returns the input as a string.
 * Note The caller is responsible for freeing the allocated memory.
 * Return: A pointer to the line read from input.
 */
char *tsh_read_line(void)
{
	#ifdef tsh_USE_STD_GETLINE
	char *line = NULL;
	ssize_t bufsize = 0; /*have getline allocate a buffer for us*/

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);/*We received an EOF*/
		}
		else
		{
			perror("tsh: getline\n");
			exit(EXIT_FAILURE);
		}
	}
	return (line);
	#else
	#define tsh_RL_BUFSIZE 1024
	int bufsize = tsh_RL_BUFSIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;

	if (!buffer)
	{
		fprintf(stderr, "tsh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		/*Read a character*/
		c = getchar();

		if (c == EOF)
		{
			exit(EXIT_SUCCESS);
		} else if (c == '\n')
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
		{
			buffer[position] = c;
		}
		position++;

		/*If we have exceeded the buffer, reallocate.*/
		if (position >= bufsize)
		{
			bufsize += tsh_RL_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
			{
				fprintf(stderr, "tsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
#endif
}

#define tsh_TOK_BUFSIZE 64
#define tsh_TOK_DELIM " \t\r\n\a"
/**
 * tsh_split_line - Split a line into tokens.
 * Splits a string into tokens using whitespace characters as delimiters.
 * Allocates memory for the tokens and returns an array of strings.
 * Note The caller is responsible for freeing the allocated memory.
 *
 * @line: The input string to be split.
 * Return: An array of strings representing the tokens.
 */
char **tsh_split_line(char *line)
{
	int bufsize = tsh_TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token, **tokens_backup;

	if (!tokens)
	{
		fprintf(stderr, "tsh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, tsh_TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += tsh_TOK_BUFSIZE;
			tokens_backup = tokens;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				free(tokens_backup);
				fprintf(stderr, "tsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, tsh_TOK_DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}
