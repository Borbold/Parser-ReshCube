#include "basic_parser.h"

#include "string.h"

int skip_comment(FILE *file, char r_b) {
  if (r_b == '#')
    while (fread(&r_b, 1, 1, file) > 0)
      if (r_b == '\n')
        return 1;
  return 0;
}

char *get_word(char r_b, char *buff, int *read_count) {
  if (*read_count == 0) {
    buff = m_malloc(MAX_LEN);
  }

  if (r_b == ' ' || r_b == '\n') {
    *read_count = 0;
  } else {
    buff[*read_count] = r_b;
    *read_count += 1;
  }
  return buff;
}

char *get_string(char r_b, FILE *file) {
  char *buff;
  int read_count = 0;
  while (fread(&r_b, 1, 1, file) > 0) {
    if (r_b == '#' || r_b == '\n') {
      break;
    }
    if (r_b != ' ') {
      buff = get_word(r_b, buff, &read_count);
    }
  }
  char *nbuff = m_malloc(strlen(buff));
  strncpy(nbuff, buff, strlen(buff));
  nbuff[strlen(buff)] = '\0';
  return nbuff;
}