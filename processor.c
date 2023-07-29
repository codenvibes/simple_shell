#include "tsh.h"

/*
 * File - processor.c
 * Auth: Terrence M.K & Tamara Lumumba
 */

/**
 * valid_exe - Checks if a given command exists in the cmd_data structure
 *	       and if the provided course exists as a regular file.
 * @data:  a pointer to the cmd_data structure containing the commands
 * @course: path to the file
 *
 * Return:  1 if the command exists and the path is a regular file, 0 otherwise
 */
int valid_exe(cmd_data *data, char *course)
{
	struct stat st;

	(void)data;
	if (!course || stat(course, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * clone_chars - Returns a new string containing the characters from src_path
 *		 between the indices start and stop.
 * @src_path: the original string from which to extract characters
 * @start: the starting index from which to extract characters (inclusive)
 * @stop:  the ending index until which to extract characters (exclusive)
 *
 * Return: a new string containing the extracted characters
 */
char *clone_chars(char *src_path, int start, int stop)
{
	static char buf[1024];
	int q = 0, h = 0;

	for (h = 0, q = start; q < stop; q++)
		if (src_path[q] != ':')
			buf[h++] = src_path[q];
	buf[h] = 0;
	return (buf);
}

/**
 * abs_path - Finds the absolute path of a given command in the given source
 *	      path
 * @data: a pointer to the cmd_data struct containing information about the
 *	  command
 * @src_path: the source path to search for the command in
 * @cmd: the command to find the path for
 *
 * Return: the absolute path of the command, or NULL if not found
 */
char *abs_path(cmd_data *data, char *src_path, char *cmd)
{
	int c = 0, current = 0;
	char *course;

	if (!src_path)
		return (NULL);
	if ((tsh_strlen(cmd) > 2) && match_prefix(cmd, "./"))
	{
		if (valid_exe(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!src_path[c] || src_path[c] == ':')
		{
			course = clone_chars(src_path, current, c);
			if (!*course)
				tsh_strcat(course, cmd);
			else
			{
				tsh_strcat(course, "/");
				tsh_strcat(course, cmd);
			}
			if (valid_exe(data, course))
				return (course);
			if (!src_path[c])
				break;
			current = c;
		}
		c++;
	}
	return (NULL);
}
