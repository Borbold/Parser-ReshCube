#include "error_checker.h"

static int check_error_miss_mirror_symbol(char symbol_1, char symbol_2,
                                          char *check_str);
static int check_error_reverse_miss_mirror_symbol(char symbol_1, char symbol_2,
                                                  char *check_str);

int check_error_all_miss_mirror_symbol(parser_result *struct_result,
                                       char *check_str) {
  char *er_str = malloc(sizeof(char));
  if (check_error_miss_mirror_symbol('[', ']', check_str) == 1) {
    sprintf(er_str, "On the line %s miss symbol ']'", check_str);
    struct_result->err_str = er_str;
    return 1;
  } else if (check_error_reverse_miss_mirror_symbol(']', '[', check_str) == 1) {
    sprintf(er_str, "On the line %s miss symbol '['", check_str);
    struct_result->err_str = er_str;
    return 1;
  }
  if (check_error_miss_mirror_symbol('{', '}', check_str) == 1) {
    sprintf(er_str, "On the line %s miss symbol '}'", check_str);
    struct_result->err_str = er_str;
    return 1;
  } else if (check_error_reverse_miss_mirror_symbol('}', '{', check_str) == 1) {
    sprintf(er_str, "On the line %s miss symbol '{'", check_str);
    struct_result->err_str = er_str;
    return 1;
  } else if (check_error_reverse_miss_mirror_symbol('}', '$', check_str) == 1) {
    sprintf(er_str, "On the line %s miss symbol '$'", check_str);
    struct_result->err_str = er_str;
    return 1;
  }
  if (check_error_miss_mirror_symbol('"', '"', check_str) == 1) {
    sprintf(er_str, "On the line %s miss symbol '%c'", check_str, '"');
    struct_result->err_str = er_str;
    return 1;
  }
  return 0;
}

int check_error_miss_mirror_symbol(char symbol_1, char symbol_2,
                                   char *check_str) {
  int er_flag = 0;
  for (int i = 0; i < strlen(check_str); i++) {
    if (check_str[i] == symbol_2 && er_flag != 0) {
      er_flag = 0;
    } else if (check_str[i] == symbol_1) {
      if (er_flag == 1)
        return er_flag;
      er_flag = 1;
    }
  }
  return er_flag;
}

int check_error_reverse_miss_mirror_symbol(char symbol_1, char symbol_2,
                                           char *check_str) {
  int er_flag = 0;
  for (int i = strlen(check_str) - 1; i >= 0; i--) {
    if (check_str[i] == symbol_2 && er_flag != 0) {
      er_flag = 0;
    } else if (check_str[i] == symbol_1) {
      if (er_flag == 1)
        return er_flag;
      er_flag = 1;
    }
  }
  return er_flag;
}

int check_error_long_line(parser_result *struct_result, int i,
                          char *string_line) {
  if (i >= 255) {
    char *err_str = "";
    sprintf(err_str, "The line is too long. Number string: %s", string_line);
    struct_result->err_str = err_str;
    return 1;
  }
  return 0;
}