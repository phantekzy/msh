#include "../include/msh.h"

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
    args = msh_split_line(line);
    status = msh_execute(args);

    free(line);
    free(args);
  } while (status);
}

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  // Ignore Ctrl+C and Ctrl+\ in the main shell loop
  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);

  msh_loop();

  return EXIT_SUCCESS;
}
