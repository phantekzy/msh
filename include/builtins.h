#ifndef BUILTINS_H
#define BUILTINS_H

int msh_cd(char **args);
int msh_exit(char **args);
int msh_help(char **args);
int msh_num_builtins();

extern char *builtin_str[];
extern int (*builtin_func[])(char **);

#endif
