#include "../include/executor.h"
#include "../include/builtins.h"
#include "../include/msh.h"
#include "../include/parser.h"
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
int msh_execute_pipe(char **commands) {
  int i = 0;
  int fd[2];
  int input_fd = 0; // stdin initially
  pid_t pid;
  while (commands[i] != NULL) {
    pipe(fd); // create pipe
    pid = fork();
    if (pid == 0) {
      // child
      signal(SIGINT, SIG_DFL);
      signal(SIGQUIT, SIG_DFL);
      // read from previous pipe
      dup2(input_fd, STDIN_FILENO);
      // if not last command → write to pipe
      if (commands[i + 1] != NULL) {
        dup2(fd[1], STDOUT_FILENO);
      }
      close(fd[0]);
      // Second stage parsing (arguments)
      char **args = msh_split_line(commands[i]);
      if (execvp(args[0], args) == -1) {
        perror("msh: pipe exec error");
      }
      exit(EXIT_FAILURE);
    } else if (pid < 0) {
      perror("msh: fork error");
      return 1;
    } else {
      // PARENT
      close(fd[1]);
      input_fd = fd[0]; // next command reads from here
    }
    i++;
  }
  int status;
  while (wait(&status) > 0);
  return 1;
}
