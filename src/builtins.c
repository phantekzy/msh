#include "../include/msh.h"

char *builtin_str[] = {"cd", "help", "exit"};

int (*builtin_func[])(char **) = {&msh_cd, &msh_help, &msh_exit};

int msh_num_builtins(void) { return sizeof(builtin_str) / sizeof(char *); }

int msh_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "msh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("msh");
    }
  }
  return 1;
}

int msh_help(char **args) {
  printf("msh: My Shell\nBuilt-in commands: cd, help, exit\n");
  return 1;
}

int msh_exit(char **args) { return 0; }
