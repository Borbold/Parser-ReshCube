#include "basic_parser.h"

#include "string.h"

int skip_comment(FILE *file, char r_b) {
  if (r_b == '#')
    while (fread(&r_b, 1, 1, file) > 0)
      if (r_b == '\n')
        return 1;
  return 0;
}

void get_word(char r_b, char *buff, int *read_count) {
  if (checker_sign(r_b)) {
    *read_count = 0;
  } else {
    buff[*read_count] = r_b;
    *read_count += 1;
    buff[*read_count] = '\0';
  }
}

char *get_string(char r_b, FILE *file) {
  char *buff = m_malloc(MAX_LEN);
  int read_count = 0, check_line = 0;
  while (fread(&r_b, 1, 1, file) > 0) {
    if (r_b == '#' || r_b == '\n' || r_b == '\t' || r_b == '\r') {
      break;
    }
    if (r_b != ' ') {
      get_word(r_b, buff, &read_count);
      check_line = 1;
    }
  }
  if (check_line == 0)
    return NULL;
  char *nbuff = m_malloc(strlen(buff));
  strncpy(nbuff, buff, strlen(buff));
  nbuff[strlen(buff)] = '\0';
  return nbuff;
}

int checker_sign(char r_b) {
  if (r_b == ' ' || r_b == '\n' || r_b == '\t' || r_b == '\r')
    return 1;
  return 0;
}