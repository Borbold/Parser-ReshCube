#include "result_parcer.h"

#include "../basic_parser.h"

static int check_operation(char r_b, FILE *file);

parser_result *read_string(parser_state *struct_init, int number_line) {
  number_line--;
  fseek(struct_init->file, 0, SEEK_SET);
  FILE *file = struct_init->file;

  parser_result *struct_result = malloc(sizeof(parser_result));

  char *buff, r_b;
  int count_line = 0;
  while (fread(&r_b, 1, 1, file) > 0) {
    if (count_line == number_line) {
      break;
    }
    if (r_b == '\n') {
      count_line++;
    }
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
  for (int i = 0; i < num_arg; i++)
    struct_result->operation_list[i].operand.name = malloc(sizeof(char));

  int i = 1, flag_LP = 0, type_op = OP_NULL;
  for (int j = 0; j < num_arg; j++) {
    for (int k = 0; i < strlen(r_value) - 1; i++, k++) {
      if (r_value[i] == '$') {
        struct_result->operation_list[j].operand.type = VALUE_EXACLY;
        i++;
      } else if (r_value[i] == '"') {
        struct_result->operation_list[j].operand.type = VALUE_CONSTANT;
        i++;
      }

      if (struct_result->operation_list[j].operand.type == VALUE_EXACLY) {
        if (r_value[i] == '{') {
          // Проверяем на открывающую скобку
          i++;
        } else if (r_value[i] == '}') {
          // Проверяем на закрывающую скобку
          i++;
        }
      }

      if (r_value[i] == '[')
        flag_LP = 1;
      if (flag_LP)
        type_op = check_operation(r_b, file);

      if (r_value[i] == ',' || r_value[i] == ']') {
        struct_result->operation_list[j].operation_type = OP_NULL;
        struct_result->operation_list[j].next_operation = NULL;
        i++;
        break;
      } else if (type_op != OP_NULL) {
        struct_result->operation_list[j].operation_type = type_op;
        struct_result->operation_list[j].next_operation =
            &struct_result->operation_list[j];
        i++;
        break;
      }
      struct_result->operation_list[j].operand.name[k] = r_value[i];
    }
  }

  printf("%s\t\t| count: %d\n", struct_result->name,
         struct_result->attribute_num);
  for (int i = 0; i < num_arg; i++)
    printf("%s\t| type: %d\n", struct_result->operation_list[i].operand.name,
           struct_result->operation_list[i].operand.type);

  free(buff);
  fclose(file);
  return struct_result;
}

int check_operation(char r_b, FILE *file) {
  switch (r_b) {
  case '>':
    fread(&r_b, 1, 1, file);
    if (r_b == '=')
      return OP_GTE;
    return OP_GT;
  case '<':
    fread(&r_b, 1, 1, file);
    if (r_b == '=')
      return OP_LTE;
    return OP_LT;
  case '=':
    fread(&r_b, 1, 1, file);
    if (r_b == '=')
      return OP_EQ;
    break;
  case '!':
    fread(&r_b, 1, 1, file);
    if (r_b == '=')
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
    fread(&r_b, 1, 1, file);
    if (r_b == '&')
      return OP_AND;
    break;
  case '|':
    fread(&r_b, 1, 1, file);
    if (r_b == '|')
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