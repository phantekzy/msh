#include "../include/msh.h"

#define MSH_TOK_BUFSIZE 64
#define MSH_TOK_DELIM " \t\r\n\a"

char *msh_read_line(void) {
  char *line = NULL;
  size_t bufsize = 0;
  ssize_t len;

  len = getline(&line, &bufsize, stdin);
  if (len == -1) {
    if (feof(stdin)) {
      printf("exit\n"); // Visual feedback on EOF (Ctrl+D)
      exit(EXIT_SUCCESS);
    } else {
      perror("msh: getline error");
      exit(EXIT_FAILURE);
    }
  }

  // Strip the trailing newline character
  if (len > 0 && line[len - 1] == '\n') {
    line[len - 1] = '\0';
  }

  return line;
}

char **msh_split_line(char *line) {
  int bufsize = MSH_TOK_BUFSIZE;
  int position = 0;
  char **tokens = malloc(bufsize * sizeof(char *));
  char *token;

  if (!tokens) {
    fprintf(stderr, "msh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, MSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position++] = token;

    if (position >= bufsize) {
      bufsize += MSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char *));
      if (!tokens) {
        fprintf(stderr, "msh: reallocation error\n");
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, MSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

int msh_has_pipe(char *line){
  return strchr(line,'|')!= NULL;
}


char **msh_split_pipe(char *line) {
  int bufsize = MSH_TOK_BUFSIZE;
  int position = 0;
  char **commands = malloc(bufsize * sizeof(char *));
  char *token;
  if (!commands) {
    fprintf(stderr, "msh: allocation error\n");
    exit(EXIT_FAILURE);
  }
  token = strtok(line, "|");  // split by pipe
  while (token != NULL) {
    commands[position++] = token;
    if (position >= bufsize) {
      bufsize += MSH_TOK_BUFSIZE;
      commands = realloc(commands, bufsize * sizeof(char *));
      if (!commands) {
        fprintf(stderr, "msh: realloc error\n");
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, "|");
  }
  commands[position] = NULL;
  return commands;
}