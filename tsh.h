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
 * struct liststr - singly linked list
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
 *struct cmd_data_struct - Struct to hold information about the current command line input.
 *@arg: pointer to a string representing the current argument being processed.
 *@argv: pointer to an array of strings representing the command line arguments.
 *@path: pointer to a string representing the path of the executable.
 *@argc: integer representing the number of command line arguments.
 *@index: unsigned integer representing the number of lines processed.
 *@err_num: the error code for exit()s
 *@linecount: integer representing whether line counting is enabled (1) or disabled (0).
 *@fname: pointer to a string representing the name of the file being processed.
 *@env: pointer to a linked list representing the environment variables.
 *@environ: pointer to an array of strings representing the environment variables.
 *@history: pointer to a linked list representing the command history.
 *@alias: pointer to a linked list representing the command aliases.
 *@env_changed: integer representing whether the environment variables have been modified (1) or not (0).
 *@status: integer representing the status of the most recent command.
 *@cmd_buf: pointer to an array of strings representing the command buffer.
 *@cmd_buf_type: integer representing the type of the command buffer. CMD_type ||, &&, ; 
 *@tsh_readfd: integer representing the file descriptor for reading input.
 *@histcount: integer representing the number of items in the command history.
 */
typedef struct cmd_data_struct
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int index;
	int err_num;
	int linecount;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type; 
	int tsh_readfd;
	int histcount;
} cmd_data;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct registry - cStruct representing a registry of built-in commands
 *@type: pointer to a character array
 *@func: pointer to a function that takes a pointer to cmd_data struct as its argument and returns an integer
 */
typedef struct registry
{
	char *type;
	int (*func)(cmd_data *);
} builtin_reg;


/* loop_exe.c */
int run_loop(cmd_data *data, char **av);
int search_run(cmd_data *);
void check_path(cmd_data *);
void fork_run(cmd_data *);

/* builtin.c */
int exit_cmd(cmd_data *);
int cd_cmd(cmd_data *);
int cd_help(cmd_data *);

/* convert_atoi.c */
int tsh_interactive(cmd_data *);

/* error_msgs.c */
int error_atoi(char *);
void display_errmsg(cmd_data *, char *);
void err_str(char *);
int err_char(char);

#endif /*TSH_H */
