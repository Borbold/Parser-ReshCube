#include "init_parcer.h"

#include "../value.h"

typedef enum {
  PROGRAM,
  VARIABLES,
  CONSTANT,
  STEPS,
} parcer_enum;
const int count_command = 4;
const char *const parcer_command[] = {
    "program:", "variables:", "constant:", "steps:"};

static char *get_word(char r_b, char *buff, int *read_count);
static int not_comment(FILE *file, char r_b);
static parser_init *attr_get_state(parser_init *struct_init, char *s_name,
                                   init_type s_type, FILE *file);

parser_init *init_parser(char *path) {
  FILE *file = fopen(path, "r");
  // 2 - две используемые команды: variables иconstant
  parser_init *struct_init = malloc(2 * sizeof(parser_init));

  char *buff, r_b;
  int read_count = 0;
  while (fread(&r_b, 1, 1, file) > 0) {
    if (not_comment(file, r_b) == 0)
      buff = get_word(r_b, buff, &read_count);
    if (read_count == 0 && strlen(buff) > 0) {
      for (int i = 0; i < count_command; i++) {
        if (strcmp(buff, parcer_command[i]) == 0 && i == PROGRAM) {
          printf("%sProgramm exist%s\n", "\033[1;34m", "\033[0m");
        } else if (strcmp(buff, parcer_command[i]) == 0 && i == VARIABLES) {
          printf("%sVariables exist%s\n", "\033[1;34m", "\033[0m");
          attr_get_state(&struct_init[INIT_VAR], "variables", INIT_VAR, file);
        } else if (strcmp(buff, parcer_command[i]) == 0 && i == CONSTANT) {
          printf("%sConstant exist%s\n", "\033[1;34m", "\033[0m");
          attr_get_state(&struct_init[INIT_CON], "constant", INIT_CON, file);
        } else if (strcmp(buff, parcer_command[i]) == 0 && i == STEPS) {
          printf("%sSteps exist%s\n", "\033[1;34m", "\033[0m");
        }
      }
    }
  }

  free(buff);
  fclose(file);
  return struct_init;
}

int not_comment(FILE *file, char r_b) {
  if (r_b == '#')
    while (fread(&r_b, 1, 1, file) > 0)
      if (r_b == '\n')
        return 1;
  return 0;
}

char *get_word(char r_b, char *buff, int *read_count) {
  if (*read_count == 0) {
    buff = malloc(MAX_LEN);
  }

  if (r_b == ' ' || r_b == '\n') {
    *read_count = 0;
  } else {
    buff[*read_count] = r_b;
    *read_count += 1;
  }
  return buff;
}

parser_init *attr_get_state(parser_init *struct_init, char *s_name,
                            init_type s_type, FILE *file) {
  struct_init->name = s_name;
  struct_init->init_type = s_type;

  int arg_num = 0;

  fpos_t pos;
  char *buff, r_b;
  int read_count = 0;
  while (fread(&r_b, 1, 1, file) > 0) {
    if (not_comment(file, r_b) == 0) {
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

  struct_init->arg_num = arg_num;
  struct_init->arg_list = malloc(arg_num * sizeof(argument_list));

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
    struct_init->arg_list[arg].name = a_name;
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
    struct_init->arg_list[arg].type = a_type;
    a_type = malloc(strlen(buff));
  }

  free(buff);
  return struct_init;
}

void free_init(parser_init *par) {
  for (int i = 0; i < par->arg_num; i++) {
    free(par[i].arg_list);
  }
  free(par->arg_list);
  free(par);
}