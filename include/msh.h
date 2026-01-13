#ifndef MSH_H
#define MSH_H

/* System Libraries  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* Constants */
#define MSH_TOK_BUFSIZE 64
#define MSH_TOK_DELIM " \t\r\n\a"

/* Function Prototypes -   */
char *msh_read_line(void);
char **msh_split_line(char *line);
int msh_execute(char **args);
int msh_launch(char **args);
int msh_num_builtins(void);

/* Built-in Commands */
int msh_cd(char **args);
int msh_help(char **args);
int msh_exit(char **args);

extern char *builtin_str[];
extern int (*builtin_func[])(char **);

#endif
