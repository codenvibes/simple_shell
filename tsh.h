#ifndef TSH_H
#define TSH_H

/* Function Declarations for main function */
void tsh_loop(void);
int main(int argc __attribute__((unused)), char **argv __attribute__((unused)));

/* Function Declarations for builtin shell commands */
int tsh_cd(char **args);
int tsh_help(char **args __attribute__((unused)));
int tsh_exit(char **args __attribute__((unused)));

/* Function Declarations for shell utility functions */
int tsh_num_builtins(void);
int tsh_launch(char **args);
int tsh_execute(char **args);
char *tsh_read_line(void);
char **tsh_split_line(char *line);

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Declaration of external variables */
extern char *builtin_str[];
extern int (*builtin_func[]) (char **);
extern size_t sizeof_builtin_str;

#endif /* TSH_H */