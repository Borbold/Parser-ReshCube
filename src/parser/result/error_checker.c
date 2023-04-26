#include "error_checker.h"

#include "../basic_parser.h"

enum err { CORRECT, WRONG };

static int check_error_miss_sign(char symbol, char *check_str);
static int check_error_miss_mirror_symbol(char symbol_1, char symbol_2,
                                          char *check_str);
static int check_error_reverse_miss_mirror_symbol(char symbol_1, char symbol_2,
                                                  char *check_str);

int check_error_all_miss_mirror_symbol(parser_result *struct_result,
                                       char *check_str) {
  char *er_str = m_malloc(sizeof(char));
  if (check_error_miss_mirror_symbol('[', ']', check_str) == WRONG) {
    sprintf(er_str, "1) On the line - %s miss symbol ']'", check_str);
    struct_result->err_str = er_str;
    return WRONG;
  } else if (check_error_reverse_miss_mirror_symbol(']', '[', check_str) ==
             WRONG) {
    sprintf(er_str, "2) On the line - %s miss symbol '['", check_str);
    struct_result->err_str = er_str;
    return WRONG;
  }

  if (check_error_miss_mirror_symbol('{', '}', check_str) == WRONG) {
    sprintf(er_str, "3) On the line - %s miss symbol '}'", check_str);
    struct_result->err_str = er_str;
    return WRONG;
  } else if (check_error_reverse_miss_mirror_symbol('}', '{', check_str) ==
             WRONG) {
    sprintf(er_str, "4) On the line - %s miss symbol '{'", check_str);
    struct_result->err_str = er_str;
    return WRONG;
  } else if (check_error_reverse_miss_mirror_symbol('}', '$', check_str) ==
             WRONG) {
    sprintf(er_str, "5) On the line - %s miss symbol '$'", check_str);
    struct_result->err_str = er_str;
    return WRONG;
  }

  if (check_error_miss_mirror_symbol('"', '"', check_str) == WRONG) {
    sprintf(er_str, "6) On the line - %s miss symbol '%c'", check_str, '"');
    struct_result->err_str = er_str;
    return WRONG;
  }

  if (check_error_miss_sign('}', check_str) == WRONG ||
      check_error_miss_sign('"', check_str) == WRONG) {
    sprintf(er_str, "7) On the line - %s miss symbol ',' or sign", check_str);
    struct_result->err_str = er_str;
    return WRONG;
  }

  mr_free(er_str);
  return CORRECT;
}

int check_error_long_line(parser_result *struct_result, int i,
                          char *string_line) {
  if (i >= 255) {
    char *err_str = "";
    sprintf(err_str, "The line is too long. Error string: %s", string_line);
    struct_result->err_str = err_str;
    return WRONG;
  }
  return CORRECT;
}

int check_sign(char r_b) {
  if (r_b != '+' || r_b != '-' || r_b != '*' || r_b != '/' || r_b != '<' ||
      r_b != '>' || r_b != ')' || r_b != '(' || r_b != '|' || r_b != '&')
    return 1;
  return 0;
}

int check_error_miss_sign(char symbol, char *check_str) {
  int er_flag = CORRECT;
  if (symbol == '}') {
    for (int i = 0; i < strlen(check_str) - 2; i++) {
      if (check_str[i] == symbol && check_str[i + 1] != ',') {
        if (check_sign(check_str[i + 1]))
          er_flag = WRONG;
      }
    }
  } else if (symbol == '"') {
    int count_sym = 0;
    for (int i = 0; i < strlen(check_str) - 2; i++) {
      if (check_str[i] == symbol)
        count_sym++;
      if (count_sym && count_sym % 2 == 0 && check_str[i] == symbol &&
          check_str[i + 1] != ',') {
        if (check_sign(check_str[i + 1]))
          er_flag = WRONG;
      }
    }
  }
  return er_flag;
}

int check_error_miss_mirror_symbol(char symbol_1, char symbol_2,
                                   char *check_str) {
  int er_flag = CORRECT;
  for (int i = 0; i < strlen(check_str); i++) {
    if (check_str[i] == symbol_2 && er_flag != CORRECT) {
      er_flag = CORRECT;
    } else if (check_str[i] == symbol_1) {
      if (er_flag == WRONG)
        return er_flag;
      er_flag = WRONG;
    }
  }
  return er_flag;
}

int check_error_reverse_miss_mirror_symbol(char symbol_1, char symbol_2,
                                           char *check_str) {
  int er_flag = CORRECT;
  for (int i = strlen(check_str) - 1; i >= 0; i--) {
    if (check_str[i] == symbol_2 && er_flag != CORRECT) {
      er_flag = CORRECT;
    } else if (check_str[i] == symbol_1) {
      if (er_flag == WRONG)
        return er_flag;
      er_flag = WRONG;
    }
  }
  return er_flag;
}