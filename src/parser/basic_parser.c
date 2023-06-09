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

int get_string(FILE *file, char *buff) {
  char r_b;
  int read_count = 0, check_line = 0, check_file = 0;
  while ((check_file = fread(&r_b, 1, 1, file)) > 0) {
    if (r_b == '\n')
      break;
    if (r_b == '#' || r_b == '\r') {
      while (fread(&r_b, 1, 1, file) > 0)
        if (r_b == '\n')
          break;
      break;
    }
    if (r_b != ' ' && r_b != '\t') {
      get_word(r_b, buff, &read_count);
      check_line = 1;
    }
  }
  if (check_line == 0)
    buff[0] = '\0';
  else
    return 0;
  return check_file == 0;
}

int checker_sign(char r_b) {
  if (r_b == ' ' || r_b == '\n' || r_b == '\t' || r_b == '\r')
    return 1;
  return 0;
}