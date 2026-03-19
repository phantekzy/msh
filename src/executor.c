#include "../include/executor.h"
#include "../include/builtins.h"
#include "../include/msh.h"

int msh_launch(char **args) {
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);

    if (execvp(args[0], args) == -1) {
      perror("msh: execution error");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("msh: fork error");
  } else {
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return 1;
}

int msh_execute(char **args) {
  if (args[0] == NULL) {
    return 1; // Return 1 to keep the shell loop running
  }

  for (int i = 0; i < msh_num_builtins(); i++) {
    if (strcmp(args[0], g_builtins[i].name) == 0) {
      return g_builtins[i].func(args);
    }
  }

  return msh_launch(args);
}
