#ifndef MSH_H
#define MSH_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MSH_TOK_BUFSIZE 64
#define MSH_TOK_DELIM " \t\r\n\a"

typedef struct s_builtin {
  char *name;
  int (*func)(char **);
} t_builtin;

#endif
