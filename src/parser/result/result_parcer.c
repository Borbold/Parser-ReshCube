#include "result_parcer.h"

#include "../basic_parser.h"

static int check_operation(char *str, int i);
static void check_curly_braces(operation *oper, char *r_value, int *i);
static void check_type_variable(operation *oper, char *r_value, int *i);
static int check_error_long_line(parser_result *struct_result, int i,
                                 int number_line);

parser_result *read_string(parser_state *struct_init, int number_line) {
  number_line--;
  fseek(struct_init->file, 0, SEEK_SET);
  FILE *file = struct_init->file;

  parser_result *struct_result = malloc(sizeof(parser_result));

  char *buff, r_b;
  int count_line = 0;
  while (fread(&r_b, 1, 1, file) > 0) {
    if (count_line == number_line)
      break;
    if (r_b == '\n')
      count_line++;
  }

  buff = get_string(r_b, file);

  int flag_N = 1;
  char *r_name = malloc(strlen(buff));
  int flag_V = 0;
  char *r_value = malloc(strlen(buff));

  int num_arg = 0;
  for (int i = 0, j = 0; i < strlen(buff); i++, j++) {
    if (flag_N) {
      if (buff[i] == ':') {
        flag_N = 0;
        flag_V = 1;
        j = 0;
        i++;
      } else
        r_name[j] = buff[i];
    }
    if (buff[i] == '[' || buff[i] == ',') {
      num_arg++;
    }
    if (flag_V) {
      r_value[j] = buff[i];
    }
  }

  struct_result->result_type = RESULT_FUN;
  struct_result->attribute_num = num_arg;
  struct_result->name = r_name;
  struct_result->operation_list = malloc(num_arg * sizeof(operation));
  char *op_name = malloc(sizeof(char));

  int i = 0, type_op = OP_NULL;
  for (int j = 0; j < num_arg; j++) {
    int flag_LP = 0;
    for (int k = 0; i < strlen(r_value) - 1; i++, k++) {
      if (check_error_long_line(struct_result, i, number_line))
        return struct_result;

      if (r_value[i] == '[' || r_value[i] == ',') {
        flag_LP = 1;
        i++;
      }

      check_type_variable(struct_result->operation_list, r_value, &i);
      check_curly_braces(struct_result->operation_list, r_value, &i);

      if (flag_LP) {
        type_op = check_operation(r_value, i);
      }

      if (r_value[i] == ',' || r_value[i] == ']') {
        struct_result->operation_list[j].operation_type = OP_NULL;
        struct_result->operation_list[j].operand.name = op_name;
        struct_result->operation_list[j].next = NULL;
        op_name = malloc(sizeof(char));
        break;
      } else if (flag_LP == 1 && type_op != OP_NULL) {
        struct_result->operation_list[j].operation_type = type_op;
        struct_result->operation_list[j].operand.name = op_name;
        operation *new_op = malloc(sizeof(operation));
        new_op->operation_type = OP_NULL;
        new_op->operand.name = malloc(sizeof(char));
        i++;
        for (int n = 0; i < strlen(r_value) - 1; i++, n++) {
          check_type_variable(new_op, r_value, &i);
          check_curly_braces(new_op, r_value, &i);

          if (r_value[i] == ',' || r_value[i] == ']') {
            new_op->next = NULL;
            i++;
            break;
          }

          new_op->operand.name[n] = r_value[i];
        }
        struct_result->operation_list[j].next = new_op;
        i++;
        op_name = malloc(sizeof(char));
        break;
      }
      op_name[k] = r_value[i];
    }
  }

  free(buff);
  fclose(file);
  return struct_result;
}

int check_error_long_line(parser_result *struct_result, int i,
                          int number_line) {
  if (i >= 255) {
    char *err_str = "";
    sprintf(err_str, "The line is too long. Number string: %d", number_line);
    struct_result->error = err_str;
    return 1;
  }
  return 0;
}

void check_type_variable(operation *oper, char *r_value, int *i) {
  if (r_value[*i] == '$') {
    oper->operand.type = VALUE_EXACLY;
    *i += 1;
  } else if (r_value[*i] == '"') {
    oper->operand.type = VALUE_CONSTANT;
    *i += 1;
  }
}

void check_curly_braces(operation *oper, char *r_value, int *i) {
  if (oper->operand.type == VALUE_EXACLY) {
    if (r_value[*i] == '{') {
      // Проверяем на открывающую скобку
      *i += 1;
    } else if (r_value[*i] == '}') {
      // Проверяем на закрывающую скобку
      *i += 1;
    }
  }
}

int check_operation(char *str, int i) {
  switch (str[i]) {
  case '>':
    if (str[i + 1] == '=')
      return OP_GTE;
    return OP_GT;
  case '<':
    if (str[i + 1] == '=')
      return OP_LTE;
    return OP_LT;
  case '=':
    if (str[i + 1] == '=')
      return OP_EQ;
    break;
  case '!':
    if (str[i + 1] == '=')
      return OP_NEQ;
    return OP_NOT;
  case '+':
    return OP_ADD;
  case '-':
    return OP_SUB;
  case '*':
    return OP_MULT;
  case '/':
    return OP_DIV;
  case '&':
    if (str[i + 1] == '&')
      return OP_AND;
    break;
  case '|':
    if (str[i + 1] == '|')
      return OP_OR;
    break;
  case '(':
    return OP_LP;
  case ')':
    return OP_RP;
  }
  return OP_NULL;
}

void free_result(parser_result *par) {
  for (int i = 0; i < par->attribute_num; i++)
    free(par[i].operation_list);
  free(par->operation_list);
  free(par);
}