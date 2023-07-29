#ifndef TSH_H
#define TSH_H

/*
 * File: tsh.h
 * Auth: Terrence M.K & Tamara Lumumba
 * Decsription: A header file containing function prototypes and data structure
 *		definitions for a simple shell program. It also includes various
 *		macros and constants used throughout the program. 
*/

/* Standard Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>

/* Constants for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Constants for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* Size of read and write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - struct representing a singly linked list.
 * @num: integer value of the node
 * @str: pointer to a string
 * @next: pointer to the next node in the linked list
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct cmd_data_struct - Struct to hold information about the current command line input.
 * @arg: pointer to a string representing the current argument being processed.
 * @argv: pointer to an array of strings representing the command line arguments.
 * @course: pointer to a string representing the path of the executable.
 * @arg_count: integer representing the number of command line arguments.
 * @index: unsigned integer representing the number of lines processed.
 * @xcode: exit_code: the error code for exit()s
 * @line_count: integer representing whether line counting is enabled (1) or disabled (0).
 * @filename: pointer to a string representing the name of the file being processed.
 * @tsh_env: pointer to a linked list representing the environment variables.
 * @environ: pointer to an array of strings representing the environment variables.
 * @cmd_log: pointer to a linked list representing the command history.
 * @tsh_alias: pointer to a linked list representing the command aliases.
 * @env_changed: integer representing whether the environment variables have been modified (1) or not (0).
 * @tsh_status: integer representing the status of the most recent command.
 * @cmd_buf: pointer to an array of strings representing the command buffer.
 * @cmd_buf_type: integer representing the type of the command buffer. CMD_type ||, &&,
 * @readfd: integer representing the file descriptor for reading input.
 * @hist_count: integer representing the number of items in the command history.
 */
typedef struct cmd_data_struct
{
	char *arg;
	char **argv;

	char *course;
	int arg_count;
	unsigned int index;
	int xcode;
	/* TODO: << >> */

	int line_count;
	char *filename;
	list_t *tsh_env;
	list_t *cmd_log;
	list_t *tsh_alias;
	/* TODO: << >> */
	char **environ;
	int env_changed;
	int tsh_status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	/* TODO: << >> */
	int hist_count;
} cmd_data;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - a built-in command and its associated function.
 *@type: stores the name of the built-in command.
 *@func: stores a pointer to the function that executes the command.
 */
typedef struct registry
{
	char *type;
	int (*func)(cmd_data *);
} builtin_reg;


/* tsh_loop.c☑️ */
int run_loop(cmd_data *, char **);
int search_run(cmd_data *);
void check_path(cmd_data *);
void tsh_fork(cmd_data *);

/* processor.c☑️ */
int valid_exe(cmd_data *, char *);
char *clone_chars(char *, int, int);
char *abs_path(cmd_data *, char *, char *);

/* loophsh.c */
/* int loophsh(char **); */

/* syserr_0.c☑️ */
void err_str(char *);
int err_char(char);
int write_fd(char c, int fd);
int _putsfd(char *str, int fd);

/* utilstr_0.c☑️ */
int tsh_strlen(char *);
int tsh_strcmp(char *, char *);
char *match_prefix(const char *, const char *);
char *tsh_strcat(char *, char *);

/* utilstr_1.c☑️ */
char *tsh_strcpy(char *, char *);
char *tsh_strdup(const char *);
void tsh_puts(char *);
int tsh_putchar(char);

/* handle_str.c☑️ */
char *cpy_str(char *, char *, int);
char *tsh_strncat(char *, char *, int);
char *tsh_strchr(char *, char);

/* tsh_strtok.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* handle_mem.c☑️ */
int tsh_dealloc(void **);

/* convert_atoi.c☑️ */
int tsh_interact(cmd_data *);
int tsh_delim(char, char *);
int tsh_isalpha(int);
int tsh_atoi(char *);

/* syserr_1.c */
int error_atoi(char *); /*☑️*/
void diplay_error(cmd_data *, char *); /*☑️*/
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtins_0.c */
int exit_cmd(cmd_data *); /*☑️*/
int cd_cmd(cmd_data *); /*☑️*/
int cd_help(cmd_data *); /*☑️*/

/* builtins_1.c */
int tsh_history(cmd_data *); /*☑️*/
int _myalias(cmd_data *);

/* fetch_line.c */
ssize_t get_input(cmd_data *);
int _getline(cmd_data *, char **, size_t *);
void sigintHandler(int);

/* fetch_data.c */
void clear_data(cmd_data *);
void set_data(cmd_data *, char **);
void free_data(cmd_data *, int);

/* tsh_env.c */
char *fetch_env(cmd_data *, const char *);
int _myenv(cmd_data *);
int _mysetenv(cmd_data *);
int _myunsetenv(cmd_data *);
int populate_env_list(cmd_data *);

/* fetch_env.c */
char **get_environ(cmd_data *);
int _unsetenv(cmd_data *, char *);
int init_env(cmd_data *, char *, char *); /*☑️*/

/* tsh_hist.c */
char *get_history_file(cmd_data *data);
int write_history(cmd_data *data);
int read_history(cmd_data *data);
int build_history_list(cmd_data *data, char *buf, int linecount);
int renumber_history(cmd_data *data);

/* utilist_0.c */
list_t *tsh_add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void tsh_free_list(list_t **);

/* utilist_1.c */
size_t tsh_list_len(const list_t *);
char **list_to_strings(list_t *);
size_t tsh_print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* tsh_params.c */
int is_chain(cmd_data *, char *, size_t *);
void check_chain(cmd_data *, char *, size_t *, size_t, size_t);
int tsh_replace_alias(cmd_data *);
int tsh_replace_vars(cmd_data *);
int tsh_replace_string(char **, char *);

#endif /*TSH_H */
