#include "../include/builtins.h"
#include "../include/msh.h"

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

  if (strcmp(path, "-") == 0) {
    path = getenv("OLDPWD");
    if (!path) {
      fprintf(stderr, "msh: cd: OLDPWD not set\n");
      return 1;
    }
    printf("%s\n", path);
  }

  if (chdir(path) != 0) {
    perror("msh: cd");
  } else {
    char cwd[1024];
    char *old_pwd = getenv("PWD");
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      setenv("OLDPWD", old_pwd ? old_pwd : "", 1);
      setenv("PWD", cwd, 1);
    }
  }
  return 1;
}

int msh_help(char **args) {
  (void)args;
  printf("msh - Minimal Shell v1.0\n");
  printf("Built-in commands:\n");
  for (int i = 0; i < msh_num_builtins(); i++) {
    printf("  - %s\n", g_builtins[i].name);
  }
  return 1;
}

int msh_exit(char **args) {
  (void)args;
  return 0;
}
