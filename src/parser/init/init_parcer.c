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
static int check_word(char *buff);

parser_state *init_parser(char *path) {
  FILE *file = fopen(path, "r");
  // 2 - две используемые команды: variables и constant
  parser_state *struct_init = m_malloc(sizeof(parser_state));
  struct_init->file = file;
  struct_init->err_str = NULL;

  char *buff = m_malloc(MAX_LEN), r_b;
  int read_count = 0, read_command[3] = {0, 0, 0}, ch_flag = 0;
  while (fread(&r_b, 1, 1, file) > 0) {
    get_word(r_b, buff, &read_count);
    ch_flag = check_word(buff);

    if (read_count == 0 && strlen(buff) > 0 && strcmp(buff, "-") != 0 &&
        ch_flag) {
      for (int i = 0; i < count_command; i++) {
        if (read_command[PROGRAM] == 0) {
          if (strcmp(buff, parser_command[i]) == 0) {
            printf("%sProgramm exist%s\n", "\033[1;34m", "\033[0m");
            read_command[PROGRAM] = 1;
            buff[0] = '\0';
            break;
          } else {
            printf("%sProgramm not exist%s\n", "\033[1;31m", "\033[0m");
            struct_init->err_str = "Programm not exist";
            return struct_init;
          }
        } else if (read_command[VARIABLES] == 0) {
          if (strcmp(buff, parser_command[VARIABLES]) == 0) {
            printf("%sVariables exist%s\n", "\033[1;34m", "\033[0m");
            attr_get_state(struct_init, file, VARIABLES);
            read_command[VARIABLES] = 1;
            buff[0] = '\0';
            break;
          } else {
            printf("%sVariables not exist%s\n", "\033[1;31m", "\033[0m");
            struct_init->err_str = "Variables not exist";
            return struct_init;
          }
        } else if (read_command[CONSTANT] == 0) {
          if (strcmp(buff, parser_command[CONSTANT]) == 0) {
            printf("%sConstant exist%s\n", "\033[1;34m", "\033[0m");
            attr_get_state(struct_init, file, CONSTANT);
            fread(&r_b, 1, 1, file);
            read_command[CONSTANT] = 1;
            buff[0] = '\0';
            break;
          } else {
            printf("%sConstant not exist%s\n", "\033[1;31m", "\033[0m");
            struct_init->err_str = "Constant not exist";
            return struct_init;
          }
        } else if (i == STEPS) {
          if (strcmp(buff, parser_command[STEPS]) == 0) {
            while (fread(&r_b, 1, 1, file) > 0)
              if (r_b == '\n')
                break;
            fgetpos(file, &struct_init->state_pos);
            printf("%sSteps exist%s\n", "\033[1;34m", "\033[0m");
            mr_free(buff);
            return struct_init;
          } else {
            printf("%sSteps not exist%s\n", "\033[1;31m", "\033[0m");
            struct_init->err_str = "Steps not exist";
            return struct_init;
          }
        }
      }
    }

    if (ch_flag == 0 && r_b == '\n')
      ch_flag = 1;
  }
}

int check_word(char *buff) {
  if (strcmp(buff, parser_command[0]) == 0 ||
      strcmp(buff, parser_command[1]) == 0 ||
      strcmp(buff, parser_command[2]) == 0 ||
      strcmp(buff, parser_command[3]) == 0) {
    return 1;
  }
  return 0;
}

parser_state *attr_get_state(parser_state *struct_init, FILE *file, int type) {
  int arg_num = 0;

  fpos_t pos;
  char *buff = m_malloc(MAX_LEN), r_b;
  int read_count = 0;
  while (fread(&r_b, 1, 1, file) > 0) {
    if (skip_comment(file, r_b) == 0 && checker_sign(r_b) == 0) {
      if (r_b != '-') {
        fsetpos(file, &pos);
        break;
      }

      // get: -
      while (fread(&r_b, 1, 1, file) > 0) {
        if (checker_sign(r_b))
          break;
        get_word(r_b, buff, &read_count);
      }
      // get: name
      while (fread(&r_b, 1, 1, file) > 0) {
        if (checker_sign(r_b))
          break;
        get_word(r_b, buff, &read_count);
      }
      // get: value
      while (fread(&r_b, 1, 1, file) > 0) {
        if (checker_sign(r_b))
          break;
        get_word(r_b, buff, &read_count);
      }

      arg_num++;
      fgetpos(file, &pos);
    }
  }

  if (type == VARIABLES)
    fill_var(struct_init, arg_num, buff);
  else if (type == CONSTANT)
    fill_con(struct_init, arg_num, buff);

  mr_free(buff);
  return struct_init;
}

void fill_var(parser_state *struct_init, int arg_num, char *buff) {
  struct_init->val_num = arg_num;
  struct_init->var_list = m_malloc(arg_num * sizeof(variable_list));

  char *a_name = m_malloc(strlen(buff));
  char *a_type = m_malloc(strlen(buff));
  int i = 0;
  for (int arg = 0; arg < arg_num; arg++) {
    for (int j = 0; i < strlen(buff); i++, j++) {
      a_name[j] = '\0';
      if (buff[i] == ':') {
        i++;
        break;
      }
      a_name[j] = buff[i];
    }
    struct_init->var_list[arg].name = a_name;
    a_name = m_malloc(strlen(buff));
    for (int j = 0; i < strlen(buff); i++, j++) {
      a_type[j] = '\0';
      if (buff[i] == '[')
        i++;
      if (buff[i] == ']') {
        i++;
        break;
      }
      a_type[j] = buff[i];
    }
    if (strcmp(a_type, "integer") == 0) {
      struct_init->var_list[arg].value = m_malloc(sizeof(int));
      struct_init->var_list[arg].type = INTEGER;
    } else if (strcmp(a_type, "decimal") == 0) {
      struct_init->var_list[arg].value = m_malloc(sizeof(float));
      struct_init->var_list[arg].type = DECIMALE;
    } else {
      struct_init->var_list[arg].value = m_malloc(sizeof(char));
      struct_init->var_list[arg].type = STRING;
    }
    a_type = m_malloc(strlen(buff));
  }
}
void fill_con(parser_state *struct_init, int arg_num, char *buff) {
  struct_init->con_num = arg_num;
  struct_init->con_list = m_malloc(arg_num * sizeof(variable_list));

  char *a_name = m_malloc(strlen(buff));
  char *a_value = m_malloc(strlen(buff));
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
    a_name = m_malloc(strlen(buff));
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
    a_value = m_malloc(strlen(buff));
  }
}

void free_init(parser_state *par) {
  for (int i = 0; i < par->val_num; i++)
    mr_free(par[i].var_list);
  mr_free(par->var_list);
  for (int i = 0; i < par->con_num; i++)
    mr_free(par[i].con_list);
  mr_free(par->con_list);
  mr_free(par);
}