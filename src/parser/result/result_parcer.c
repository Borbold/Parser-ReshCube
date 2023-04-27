#include "result_parcer.h"

#include "../basic_parser.h"
#include "error_checker.h"

static int check_operation(char *str, int i);
static void check_curly_braces(operation *oper, char *r_value, int *i);
static void check_type_variable(operation *oper, char *r_value, int *i);

parser_result *read_string(parser_state *struct_init) {
  FILE *file = struct_init->file;

  parser_result *struct_result = m_malloc(sizeof(parser_result));
  struct_result->err_str = NULL;

  char *buff = malloc(MAX_LEN);
  do {
    get_string(file, buff);
  } while (buff == NULL);
  if (check_error_all_miss_mirror_symbol(struct_result, buff) == 1)
    return struct_result;

  int flag_N = 1;
  char r_name[strlen(buff)];
  int flag_V = 0;
  char r_value[strlen(buff)];

  int num_arg = 0;
  for (int i = 1, j = 0; i < strlen(buff); i++, j++) {
    if (flag_N) {
      if (buff[i] == ':') {
        flag_N = 0;
        flag_V = 1;
        r_name[j] = '\0';
        j = 0;
        i++;
      } else {
        r_name[j] = buff[i];
      }
    }
    if (buff[i] == '[' || buff[i] == ',') {
      num_arg++;
    }
    if (flag_V) {
      r_value[j] = buff[i];
      if (buff[i] == ']')
        r_value[j + 1] = '\0';
    }
  }

  struct_result->result_type = RESULT_FUN;
  struct_result->attribute_num = num_arg;
  struct_result->name = malloc(strlen(r_name) + 1);
  sprintf(struct_result->name, "%s", r_name);
  struct_result->operation_list = m_malloc(num_arg * sizeof(operation));
  char op_name[MAX_LEN];

  int i = 0, type_op = OP_NULL;
  for (int j = 0; j < num_arg; j++) {
    int flag_LP = 0;
    for (int k = 0; i < strlen(r_value) - 1; i++, k++) {
      op_name[k] = '\0';
      if (check_error_long_line(struct_result, i, buff))
        return struct_result;

      if (r_value[i] == '[' || r_value[i] == ',') {
        flag_LP = 1;
        i++;
      }

      check_type_variable(&struct_result->operation_list[j], r_value, &i);
      if (struct_result->operation_list[j].operand.type == VALUE_EXACLY)
        check_curly_braces(&struct_result->operation_list[j], r_value, &i);

      if (flag_LP)
        type_op = check_operation(r_value, i);

      if (r_value[i] == ',' || r_value[i] == ']') {
        struct_result->operation_list[j].operation_type = OP_NULL;
        struct_result->operation_list[j].operand.name =
            malloc(strlen(op_name) + 1);
        sprintf(struct_result->operation_list[j].operand.name, "%s", op_name);
        struct_result->operation_list[j].next = NULL;
        break;
      } else if (flag_LP == 1 && type_op != OP_NULL) {
        struct_result->operation_list[j].operation_type = type_op;
        struct_result->operation_list[j].operand.name =
            malloc(strlen(op_name) + 1);
        sprintf(struct_result->operation_list[j].operand.name, "%s", op_name);
        operation *new_op = m_malloc(sizeof(operation));
        new_op->operation_type = OP_NULL;
        new_op->operand.name = m_malloc(MAX_LEN);
        i++;
        for (int n = 0; i < strlen(r_value) - 1; i++, n++) {
          check_type_variable(new_op, r_value, &i);
          check_curly_braces(new_op, r_value, &i);

          if (r_value[i] == ',' || r_value[i] == ']') {
            new_op->operand.name[n] = '\0';
            new_op->next = NULL;
            i++;
            break;
          }

          new_op->operand.name[n] = r_value[i];
        }
        struct_result->operation_list[j].next = new_op;
        i++;
        break;
      }
      op_name[k] = r_value[i];
    }
  }

  mr_free(buff);
  return struct_result;
}

void set_fposition(FILE *file, fpos_t pos) { fsetpos(file, &pos); }
fpos_t get_fposition(FILE *file, fpos_t pos) {
  fgetpos(file, &pos);
  return pos;
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
  while (par->operation_list->next) {
    operation *op = par->operation_list;
    par->operation_list = par->operation_list->next;
    free(op);
  }
  mr_free(par);
}