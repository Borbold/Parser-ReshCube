#include "parser.h"

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "../types.h"

#define DATA_FILE "./test/tests_scripts.txt"
#define LENGTH_BUFF 255

static void read_param(FILE *data_file);
static void read_variable(FILE *data_file);
static void read_constant(FILE *data_file);

static void make_blank(char *name);

// Получить целое слово
char *fill_out(char r_b, char *buff, int *read_count) {
  if (r_b == ' ' || r_b == '\n') {
    buff = malloc(LENGTH_BUFF);
    *read_count = 0;
  } else {
    buff[*read_count] = r_b;
    *read_count += 1;
  }
  return buff;
}

// Получить целую строку
char *get_string(FILE *file) {
  int read_count = 0;
  char *buff = malloc(LENGTH_BUFF);
  char r_b;
  while (fread(&r_b, 1, 1, file) > 0) {
    if (r_b == '\n')
      break;
    buff[read_count] = r_b;
    read_count += 1;
  }
  return buff;
}

parser_state *attr_get_type(char *name, head_type type) {
  parser_state *struct_attr = malloc(sizeof(parser_state));
  struct_attr->name = name;
  struct_attr->type = type;
  return struct_attr;
}

attribute_type get_type(char *str) {
  if (strcmp(str, "INT") == 0)
    return INT;
  else if (strcmp(str, "DEC") == 0)
    return DEC;
  else if (strcmp(str, "STR") == 0)
    return STR;
}

parser_state *attr_get_all(char *name, head_type type, FILE *file) {
  get_string(file);
  fpos_t pos;
  int count_var = 0;
  parser_state *struct_attr = malloc(sizeof(parser_state));
  struct_attr->attribute = malloc(count_var * sizeof(attribute));
  while (1) {
    fgetpos(file, &pos);
    char *buff = get_string(file);
    if (buff[0] != '-') {
      fsetpos(file, &pos);
      break;
    }

    struct_attr->name = name;
    struct_attr->type = type;

    struct_attr->attribute[count_var].name = malloc(20);
    struct_attr->attribute[count_var].val.string = malloc(20);

    int n, m;
    for (n = 2, m = 0; n < strlen(buff) - 1; n++) {
      if (buff[n] == ':') {
        n += 2;
        break;
      } else {
        struct_attr->attribute[count_var].name[m++] = buff[n];
      }
    }

    for (m = 0; n < strlen(buff) - 1; n++) {
      if (buff[n] == ' ') {
        n++;
        break;
      } else if (buff[n] != '[' && buff[n] != ',') {
        struct_attr->attribute[count_var].val.string[m++] = buff[n];
      }
    }

    char *type = malloc(sizeof(buff));
    for (m = 0; n < strlen(buff) - 1; n++) {
      if (buff[n] == ']') {
        break;
      } else {
        type[m++] = buff[n];
      }
    }
    struct_attr->attribute[count_var].type = get_type(type);
    count_var++;
  }
  struct_attr->num_attr = count_var;
  return struct_attr;
}

parser_state *parse_header(FILE *file, int number_line) {
  int read_count = 0;
  char *buff = malloc(LENGTH_BUFF);
  char r_b;
  while (fread(&r_b, 1, 1, file) > 0) {
    buff = fill_out(r_b, buff, &read_count);

    for (int basic_count = number_line;
         basic_count < sizeof(basic_command) / sizeof(basic_command[0]) - 1;
         basic_count++) {
      if (strcmp(buff, basic_command[basic_count]) == 0) {
        if (strcmp(buff, basic_command[PROGRAM]) == 0) {
          printf("%sProgramm exist%s\n", "\033[1;34m", "\033[0m");
          number_line++;
          return attr_get_type("NULL", NUL_H);
        } else if (number_line == PROGRAM) {
          return attr_get_type((char *)basic_command[PROGRAM], ERR_H);
        }

        if (strcmp(buff, basic_command[VARIABLES]) == 0) {
          printf("%sVariables exist%s\n", "\033[1;34m", "\033[0m");
          number_line++;
          return attr_get_all((char *)basic_command[VARIABLES], VAR, file);
        } else if (number_line == VARIABLES) {
          return attr_get_type((char *)basic_command[VARIABLES], ERR_H);
        }

        if (strcmp(buff, basic_command[CONSTANT]) == 0) {
          printf("%sConstant exist%s\n", "\033[1;34m", "\033[0m");
          number_line++;
          return attr_get_all((char *)basic_command[CONSTANT], CON, file);
        } else if (number_line == CONSTANT) {
          return attr_get_type((char *)basic_command[CONSTANT], ERR_H);
        }

        if (strcmp(buff, basic_command[STEPS]) == 0) {
          printf("%sSteps exist%s\n", "\033[1;34m", "\033[0m");
          number_line++;
          return attr_get_type("NULL", NUL_H);
        } else if (number_line == STEPS) {
          return attr_get_type((char *)basic_command[STEPS], ERR_H);
        }
      }
    }
  }

  free(buff);
  fclose(file);
  return NULL;
}

parser_state *init_parser(FILE *file, int number_line) {
  parser_state *struct_attr = parse_header(file, number_line);
  return struct_attr;
}

parser_result *parse_body(FILE *file, int number_line) {
  int read_count = 0;
  char *buff = malloc(LENGTH_BUFF);
  char r_b;
  while (fread(&r_b, 1, 1, file) > 0) {
    buff = fill_out(r_b, buff, &read_count);

    if (r_b == '-')
      printf("%s\n", buff);
  }

  free(buff);
  fclose(file);
  return NULL;
}

parser_result *read_string(FILE *file, int number_line) {
  parser_result *struct_attr = parse_body(file, number_line);
  return struct_attr;
}

void main() {
  FILE *file = fopen(DATA_FILE, "r");
  // Парсим заголовок файла
  parser_state *struct_attr;
  for (int c = 0; c < sizeof(basic_string); c++) {
    struct_attr = init_parser(file, c);

    if (struct_attr) {
      switch (struct_attr->type) {
      case ERR_H:
        printf("\n%sERORRE! Name attribute: '%s'%s\n", "\033[0;31m",
               struct_attr->name, "\033[0m");
        break;
      case VAR:
        for (int i = 0; i < struct_attr->num_attr; i++) {
          printf("%sName: %s; Type: %d; Attribute[Name: %s; Type: %d; Val: "
                 "%s;]%s\n",
                 "\033[1;36m", struct_attr->name, struct_attr->type,
                 struct_attr->attribute[i].name, struct_attr->attribute[i].type,
                 struct_attr->attribute[i].val.string, "\033[0m");
        }
        break;
      case CON:
        for (int i = 0; i < struct_attr->num_attr; i++) {
          printf("%sName: %s; Type: %d; Attribute[Name: %s; Type: %d; Val: "
                 "%s;]%s\n",
                 "\033[1;36m", struct_attr->name, struct_attr->type,
                 struct_attr->attribute[i].name, struct_attr->attribute[i].type,
                 struct_attr->attribute[i].val.string, "\033[0m");
        }
        break;
      }
    } else {
      printf("\n%sERORRE! Attribute is NULL!%s\n", "\033[0;31m", "\033[0m");
    }
  }

  get_string(file);

  // Парсим строку из тела файла
  read_string(file, 2);
}

/* Make */
void make_param(char *name, char *type) {
  printf("Create param %s with type %s\n", name, type);
}
void make_variable(char *name, char *type) {
  printf("Create variable %s with type %s\n", name, type);
}
void make_constant(char *name, char *type) {
  printf("Create constant %s with type %s\n", name, type);
}
void make_blank(char *name) { printf("%s\n", name); }
/* Make */

/* Read */
void read_param(FILE *data_file) {
  printf("%sParams exist%s\n", "\033[1;34m", "\033[0m");
  make_param(get_string(data_file), "TYPE");
}
void read_variable(FILE *data_file) {
  printf("%sVariables exist%s\n", "\033[1;34m", "\033[0m");
  make_param(get_string(data_file), "TYPE");
}
void read_constant(FILE *data_file) {
  printf("%sConstant exist%s\n", "\033[1;34m", "\033[0m");
  make_param(get_string(data_file), "TYPE");
}
/* Read */

/*Run*/
void send_run() { printf("Send to run\n"); }
/*Run*/