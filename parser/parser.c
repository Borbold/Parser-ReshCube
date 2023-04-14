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

char *get_buff(FILE *data_file) {
  int read_count = 0;
  char *buff = malloc(LENGTH_BUFF);
  char r_b;
  while (fread(&r_b, 1, 1, data_file) > 0) {
    if (r_b == '\n')
      break;
    fill_out(r_b, buff, &read_count);
  }
  return buff;
}

basic_attr *attr_get(char *name, str_type type) {
  basic_attr *attr = malloc(sizeof(attr));
  attr->name = name;
  attr->type = type;
  return attr;
}

basic_attr *parse_file(FILE *data_file, int lines_passed) {
  int read_count = 0;
  char *buff = malloc(LENGTH_BUFF);
  char r_b;
  while (fread(&r_b, 1, 1, data_file) > 0) {
    buff = fill_out(r_b, buff, &read_count);

    for (int basic_count = lines_passed;
         basic_count < sizeof(basic_command) / sizeof(basic_command[0]) - 1;
         basic_count++) {
      if (strcmp(buff, basic_command[basic_count]) == 0) {
        if (strcmp(buff, basic_command[PROGRAM]) == 0) {
          printf("%sProgramm exist%s\n", "\033[1;34m", "\033[0m");
          lines_passed++;
          return attr_get("NULL", NUL);
        } else if (lines_passed == PROGRAM) {
          return attr_get((char *)basic_command[PROGRAM], ERR);
        }

        if (strcmp(buff, basic_command[VARIABLES]) == 0) {
          printf("%sVariables exist%s\n", "\033[1;34m", "\033[0m");
          lines_passed++;
          return attr_get("NULL", NUL);
        } else if (lines_passed == VARIABLES) {
          return attr_get((char *)basic_command[VARIABLES], ERR);
        }

        /*if (strcmp(buff, basic_command[PARAMS]) == 0) {
          printf("%sParams exist%s\n", "\033[1;34m", "\033[0m");
        } else if (strcmp(buff, basic_command[VARIABLES]) == 0) {
          printf("%sVariables exist%s\n", "\033[1;34m", "\033[0m");
        } else if (strcmp(buff, basic_command[START_TIME]) == 0) {
          printf("%sStart time exist%s\n", "\033[1;33m", "\033[0m");
          make_blank(get_buff(data_file));
        } else if (strcmp(buff, basic_command[CONSTANT]) == 0) {
          printf("%sConstant exist%s\n", "\033[1;34m", "\033[0m");
        } else if (strcmp(buff, basic_command[LATITUDE]) == 0) {
          printf("%sLATITUDE exist%s\n", "\033[1;34m", "\033[0m");
          make_blank(get_buff(data_file));
        } else if (strcmp(buff, basic_command[LONGITUDE]) == 0) {
          printf("%sLONGITUDE exist%s\n", "\033[1;34m", "\033[0m");
          make_blank(get_buff(data_file));
        } else if (strcmp(buff, basic_command[STEPS]) == 0) {
          printf("%sSteps exist. Send to run.%s\n", "\033[1;34m", "\033[0m");
        } else if (strcmp(buff, basic_command[WAIT_COORDINATES]) == 0) {
          printf("%sWAIT_COORDINATES exist%s\n", "\033[1;34m", "\033[0m");
          make_blank(get_buff(data_file));
        } else if (strcmp(buff, basic_command[ORIENTATION]) == 0) {
          printf("%sORIENTATION exist%s\n", "\033[1;34m", "\033[0m");
          make_blank(get_buff(data_file));
        } else if (strcmp(buff, basic_command[PAYLOAD_POWER]) == 0) {
          printf("%sPAYLOAD_POWER exist%s\n", "\033[1;34m", "\033[0m");
          make_blank(get_buff(data_file));
        } else if (strcmp(buff, basic_command[WAIT]) == 0) {
          printf("%sWait exist%s\n", "\033[1;35m", "\033[0m");
          make_blank(get_buff(data_file));
        } else if (strcmp(buff, basic_command[CREATE_METER]) == 0) {
          printf("%sCREATE_METER exist%s\n", "\033[1;34m", "\033[0m");
          make_blank(get_buff(data_file));
        } else if (strcmp(buff, basic_command[ADD_CHANAL_METER]) == 0) {
          printf("%sADD_CHANAL_METER exist%s\n", "\033[1;34m", "\033[0m");
          make_blank(get_buff(data_file));
        } else if (strcmp(buff, basic_command[RUN_METER]) == 0) {
          printf("%sRUN_METER exist%s\n", "\033[1;34m", "\033[0m");
          make_blank(get_buff(data_file));
        } else if (strcmp(buff, basic_command[STOP_METER]) == 0) {
          printf("%sSTOP_METER exist%s\n", "\033[1;34m", "\033[0m");
          make_blank(get_buff(data_file));
        } else if (strcmp(buff, basic_command[EXIT]) == 0) {
          printf("%sEXIT exist%s\n", "\033[1;34m", "\033[0m");
        }*/
      }
    }
  }

  free(buff);
  fclose(data_file);
  return NULL;
}

void main() {
  FILE *file = fopen(DATA_FILE, "r");
  for (int count_command = 0; count_command < 2; count_command++) {
    basic_attr *attr = parse_file(file, count_command);
    if (attr) {
      switch (attr->type) {
      case ERR:
        printf("\n%sERORRE! Name attribute: '%s'%s\n", "\033[0;31m", attr->name,
               "\033[0m");
        break;
      }
    } else {
      printf("\n%sERORRE! Attribute is NULL!%s\n", "\033[0;31m", "\033[0m");
    }
  }
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
  make_param(get_buff(data_file), "TYPE");
}
void read_variable(FILE *data_file) {
  printf("%sVariables exist%s\n", "\033[1;34m", "\033[0m");
  make_param(get_buff(data_file), "TYPE");
}
void read_constant(FILE *data_file) {
  printf("%sConstant exist%s\n", "\033[1;34m", "\033[0m");
  make_param(get_buff(data_file), "TYPE");
}
/* Read */

/*Run*/
void send_run() { printf("Send to run\n"); }
/*Run*/