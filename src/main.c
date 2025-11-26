#include <stdio.h>
#include <stdlib.h>

int main() {
  while (1) {
    // 1. Print prompt
    printf("msh> ");
    fflush(stdout);

    // 2. Prepare input buffer
    char *line = NULL;
    size_t bufsize = 0;

    // 3. Read input
    ssize_t characters = getline(&line, &bufsize, stdin);

    // 4. Check for EOF (Ctrl+D)
    if (characters == -1) {
      printf("\n");
      break; // exit the shell
    }

    // 5. Echo input
    printf("You typed: %s", line);

    // 6. Free memory
    free(line);
  }

  return 0;
}
