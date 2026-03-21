#include "../include/msh.h"
#include <ctype.h>

char *msh_expand_vars(char *line) {
  if (!line)
    return NULL;

  // Allocate a buffer for the expanded string
  char *expanded = malloc(2048);
  if (!expanded)
    return line;

  int i = 0, j = 0;

  while (line[i] != '\0' && j < 2047) {
    // Detect $ followed by an alphanumeric character or underscore
    if (line[i] == '$' && (isalnum(line[i + 1]) || line[i + 1] == '_')) {
      i++;
      char var_name[128];
      int k = 0;

      // Extract the variable name
      while (line[i] != '\0' && (isalnum(line[i]) || line[i] == '_') &&
             k < 127) {
        var_name[k++] = line[i++];
      }
      var_name[k] = '\0';

      // Lookup the value in the system environment
      char *value = getenv(var_name);
      if (value) {
        while (*value && j < 2047) {
          expanded[j++] = *value++;
        }
      }
    } else {
      expanded[j++] = line[i++];
    }
  }
  expanded[j] = '\0';

  // Free the raw input line and return the translated one
  free(line);
  return expanded;
}
