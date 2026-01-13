#include "../include/msh.h"

char *msh_read_line(void) {
  char *line = NULL;
  size_t bufsize = 0;

  if (getline(&line, &bufsize, stdin) == -1) {
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);
    } else {
      perror("msh: getline");
      exit(EXIT_FAILURE);
    }
  }
  return line;
}

char **msh_split_line(char *line) {
  int bufsize = MSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char *));
  char *token;

  if (!tokens) {
    fprintf(stderr, "msh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, MSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += MSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char *));
      if (!tokens) {
        fprintf(stderr, "msh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, MSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}
