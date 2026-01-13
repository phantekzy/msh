#include "../include/msh.h"

void msh_loop(void) {
  char *line;
  char **args;
  int status;

  do {
    printf("msh > ");
    line = msh_read_line();
    args = msh_split_line(line);
    status = msh_execute(args);

    free(line);
    free(args);
  } while (status);
}

int main(int argc, char **argv) {
  msh_loop();
  return EXIT_SUCCESS;
}
