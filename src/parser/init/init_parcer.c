#include "init_parcer.h"

#include "../basic_parser.h"
#include "../value.h"

typedef enum {
  PROGRAM,
  VARIABLES,
  CONSTANT,
  STEPS,
} parser_enum;
const int count_command = 4;
const char *const parser_command[] = {
    "program:", "variables:", "constant:", "steps:"};

static parser_state *attr_get_state(parser_state *struct_init, FILE *file,
                                    int type);
static void fill_var(parser_state *struct_init, int arg_num, char *buff);
static void fill_con(parser_state *struct_init, int arg_num, char *buff);

parser_state *init_parser(char *path) {
  FILE *file = fopen(path, "r");
  // 2 - две используемые команды: variables и constant
  parser_state *struct_init = malloc(sizeof(parser_state));
  struct_init->file = file;

  char *buff, r_b;
  int read_count = 0;
  while (fread(&r_b, 1, 1, file) > 0) {
    if (skip_comment(file, r_b) == 0)
      buff = get_word(r_b, buff, &read_count);
    if (read_count == 0 && strlen(buff) > 0) {
      for (int i = 0; i < count_command; i++) {
        if (strcmp(buff, parser_command[i]) == 0 && i == PROGRAM) {
          printf("%sProgramm exist%s\n", "\033[1;34m", "\033[0m");
        } else if (strcmp(buff, parser_command[i]) == 0 && i == VARIABLES) {
          printf("%sVariables exist%s\n", "\033[1;34m", "\033[0m");
          attr_get_state(struct_init, file, VARIABLES);
        } else if (strcmp(buff, parser_command[i]) == 0 && i == CONSTANT) {
          printf("%sConstant exist%s\n", "\033[1;34m", "\033[0m");
          attr_get_state(struct_init, file, CONSTANT);
        } else if (strcmp(buff, parser_command[i]) == 0 && i == STEPS) {
          printf("%sSteps exist%s\n", "\033[1;34m", "\033[0m");
        }
      }
    }
  }

  free(buff);
  return struct_init;
}

parser_state *attr_get_state(parser_state *struct_init, FILE *file, int type) {
  int arg_num = 0;

  fpos_t pos;
  char *buff, r_b;
  int read_count = 0;
  while (fread(&r_b, 1, 1, file) > 0) {
    if (skip_comment(file, r_b) == 0) {
      if (r_b != '-') {
        fsetpos(file, &pos);
        break;
      }

      // get: -
      while (fread(&r_b, 1, 1, file) > 0) {
        if (r_b == ' ')
          break;
        buff = get_word(r_b, buff, &read_count);
      }
      // get: name
      while (fread(&r_b, 1, 1, file) > 0) {
        if (r_b == ' ')
          break;
        buff = get_word(r_b, buff, &read_count);
      }
      // get: value
      while (fread(&r_b, 1, 1, file) > 0) {
        if (r_b == ' ' || r_b == '\n')
          break;
        buff = get_word(r_b, buff, &read_count);
      }

      arg_num++;
      fgetpos(file, &pos);
    }
  }

  if (type == VARIABLES)
    fill_var(struct_init, arg_num, buff);
  else if (type == CONSTANT)
    fill_con(struct_init, arg_num, buff);

  free(buff);
  return struct_init;
}

void fill_var(parser_state *struct_init, int arg_num, char *buff) {
  struct_init->val_num = arg_num;
  struct_init->var_list = malloc(arg_num * sizeof(variable_list));

  char *a_name = malloc(strlen(buff));
  char *a_type = malloc(strlen(buff));
  int i = 0;
  for (int arg = 0; arg < arg_num; arg++) {
    for (int j = 0; i < strlen(buff); i++, j++) {
      if (buff[i] == ':') {
        i++;
        break;
      }
      a_name[j] = buff[i];
    }
    struct_init->var_list[arg].name = a_name;
    a_name = malloc(strlen(buff));
    for (int j = 0; i < strlen(buff); i++, j++) {
      if (buff[i] == '[')
        i++;
      if (buff[i] == ']') {
        i++;
        break;
      }
      a_type[j] = buff[i];
    }
    struct_init->var_list[arg].type = a_type;
    if (strcmp(a_type, "integer") == 0)
      struct_init->var_list[arg].value = malloc(sizeof(int));
    else if (strcmp(a_type, "decimal") == 0)
      struct_init->var_list[arg].value = malloc(sizeof(float));
    else
      struct_init->var_list[arg].value = malloc(sizeof(char));
    a_type = malloc(strlen(buff));
  }
}
void fill_con(parser_state *struct_init, int arg_num, char *buff) {
  struct_init->con_num = arg_num;
  struct_init->con_list = malloc(arg_num * sizeof(variable_list));

  char *a_name = malloc(strlen(buff));
  char *a_value = malloc(strlen(buff));
  int i = 0;
  for (int arg = 0; arg < arg_num; arg++) {
    for (int j = 0; i < strlen(buff); i++, j++) {
      if (buff[i] == ':') {
        i++;
        break;
      }
      a_name[j] = buff[i];
    }
    struct_init->con_list[arg].name = a_name;
    a_name = malloc(strlen(buff));
    for (int j = 0; i < strlen(buff); i++, j++) {
      if (buff[i] == '[')
        i++;
      if (buff[i] == ']') {
        i++;
        break;
      }
      a_value[j] = buff[i];
    }
    struct_init->con_list[arg].value = a_value;
    a_value = malloc(strlen(buff));
  }
}

void free_init(parser_state *par) {
  for (int i = 0; i < par->val_num; i++)
    free(par[i].var_list);
  free(par->var_list);
  for (int i = 0; i < par->con_num; i++)
    free(par[i].con_list);
  free(par->con_list);
  free(par);
}