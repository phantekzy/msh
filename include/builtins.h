#ifndef BUILTINS_H
#define BUILTINS_H

#include "msh.h"

int msh_cd(char **args);
int msh_exit(char **args);
int msh_help(char **args);
int msh_num_builtins(void);

extern t_builtin g_builtins[];

#endif
