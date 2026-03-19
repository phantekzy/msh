#include "../include/msh.h"

typedef struct s_builtin {
  char *name;
  int (*func)(char **);
} t_builtin;

int msh_cd(char **args);
int msh_help(char **args);
int msh_exit(char **args);

t_builtin g_builtins[] = {
    {"cd", &msh_cd}, {"help", &msh_help}, {"exit", &msh_exit}};

int msh_num_builtins(void) { return sizeof(g_builtins) / sizeof(t_builtin); }

int msh_cd(char **args) {
  char *path = args[1];

  if (path == NULL) {
    path = getenv("HOME");
    if (path == NULL) {
      fprintf(stderr, "msh: cd: HOME not set\n");
      return 1;
    }
  }

  if (chdir(path) != 0) {
    perror("msh: cd");
  } else {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      setenv("OLDPWD", getenv("PWD") ? getenv("PWD") : "", 1);
      setenv("PWD", cwd, 1);
    }
  }
  return 1;
}

int msh_help(char **args) {
  (void)args; // Avoid unused parameter warning
  printf("msh - Minimal Shell\n");
  printf("Type program names and arguments, and hit enter.\n");
  for (int i = 0; i < msh_num_builtins(); i++) {
    printf("  - %s\n", g_builtins[i].name);
  }
  return 1;
}

int msh_exit(char **args) {
  (void)args;
  return 0;
}
