#include "../include/executor.h"
#include "../include/msh.h"
#include "../include/parser.h"

void msh_loop(void) {
  char *line;
  char **args;
  int status;

  do {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      printf("\033[1;32mmsh\033[0m:\033[1;34m%s\033[0m$ ", cwd);
    } else {
      printf("msh > ");
    }

    line = msh_read_line();

    line = msh_expand_vars(line);

    if (msh_has_pipe(line)) {
      char **commands = msh_split_pipe(line);
      status = msh_execute_pipe(commands);
      free(commands);
    } else {
      args = msh_split_line(line);
      status = msh_execute(args);
      free(args);
    }

    free(line);

  } while (status);
}

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);

  msh_loop();

  return EXIT_SUCCESS;
}
