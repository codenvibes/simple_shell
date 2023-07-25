#ifndef TSH_H
#define TSH_H

/* Function Declarations for builtin shell commands */
int tsh_cd(char **args);
int tsh_help(char **args);
int tsh_exit(char **args);

/* Function Declarations for shell utility functions */
int tsh_num_builtins(void);
char *tsh_read_line(void);
char **tsh_split_line(char *line);
int tsh_execute(char **args);

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern char *builtin_str[];
extern int (*builtin_func[]) (char **);

#endif /* TSH_H */