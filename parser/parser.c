#include "parser.h"

#include "stdint.h"
#include "stdio.h"
#include "string.h"

#define DATA_FILE "./test/tests_scripts.txt"

static void read_param(FILE *data_file);
static void read_variable(FILE *data_file);
static void read_constant(FILE *data_file);

void main() {
  FILE *data_file = fopen(DATA_FILE, "r");
  char buff[64];
  while (fscanf((FILE *)data_file, "%s", buff) != EOF) {
    for (int basic_count = 0;
         basic_count < sizeof(basic_command) / sizeof(basic_command[0]) - 1;
         basic_count++) {
      if (strcmp(buff, basic_command[basic_count]) == 0) {
        if (strcmp(buff, basic_command[PROGRAM]) == 0) {
          printf("%sPROGRAM exist%s\n", "\033[1;34m", "\033[0m");
        } else if (strcmp(buff, basic_command[PARAMS]) == 0) {
          read_param(data_file);
        } else if (strcmp(buff, basic_command[VARIABLES]) == 0) {
          read_variable(data_file);
        } else if (strcmp(buff, basic_command[START_TIME]) == 0) {
          printf("%sStart time exist%s\n", "\033[1;33m", "\033[0m");
          char var[200];
          fscanf((FILE *)data_file, "%s", var);
          printf("%s\n", var);
        } else if (strcmp(buff, basic_command[CONSTANT]) == 0) {
          read_constant(data_file);
        } else if (strcmp(buff, basic_command[LATITUDE]) == 0) {
          printf("%sLATITUDE exist%s\n", "\033[1;34m", "\033[0m");
          char var[200];
          fscanf((FILE *)data_file, "%s", var);
          printf("%s\n", var);
        } else if (strcmp(buff, basic_command[LONGITUDE]) == 0) {
          printf("%sLONGITUDE exist%s\n", "\033[1;34m", "\033[0m");
          char var[200];
          fscanf((FILE *)data_file, "%s", var);
          printf("%s\n", var);
        } else if (strcmp(buff, basic_command[STEPS]) == 0) {
          printf("%sSTEPS exist%s\n", "\033[1;34m", "\033[0m");
          char var[200];
          fscanf((FILE *)data_file, "%s", var);
          printf("%s\n", var);
        } else if (strcmp(buff, basic_command[WAIT_COORDINATES]) == 0) {
          printf("%sWAIT_COORDINATES exist%s\n", "\033[1;34m", "\033[0m");
          char var[200];
          fscanf((FILE *)data_file, "%s", var);
          printf("%s\n", var);
        } else if (strcmp(buff, basic_command[ORIENTATION]) == 0) {
          printf("%sORIENTATION exist%s\n", "\033[1;34m", "\033[0m");
          char var[200];
          fscanf((FILE *)data_file, "%s", var);
          printf("%s\n", var);
        } else if (strcmp(buff, basic_command[PAYLOAD_POWER]) == 0) {
          printf("%sPAYLOAD_POWER exist%s\n", "\033[1;34m", "\033[0m");
          char var[200];
          fscanf((FILE *)data_file, "%s", var);
          printf("%s\n", var);
        } else if (strcmp(buff, basic_command[WAIT]) == 0) {
          printf("%sWait exist%s\n", "\033[1;35m", "\033[0m");
          char var[200];
          fscanf((FILE *)data_file, "%s", var);
          printf("%s\n", var);
        } else if (strcmp(buff, basic_command[CREATE_METER]) == 0) {
          printf("%sCREATE_METER exist%s\n", "\033[1;34m", "\033[0m");
          char var[200];
          fscanf((FILE *)data_file, "%s", var);
          printf("%s\n", var);
        } else if (strcmp(buff, basic_command[ADD_CHANAL_METER]) == 0) {
          printf("%sADD_CHANAL_METER exist%s\n", "\033[1;34m", "\033[0m");
          char var[200];
          fscanf((FILE *)data_file, "%s", var);
          printf("%s\n", var);
        } else if (strcmp(buff, basic_command[RUN_METER]) == 0) {
          printf("%sRUN_METER exist%s\n", "\033[1;34m", "\033[0m");
          char var[200];
          fscanf((FILE *)data_file, "%s", var);
          printf("%s\n", var);
        } else if (strcmp(buff, basic_command[STOP_METER]) == 0) {
          printf("%sSTOP_METER exist%s\n", "\033[1;34m", "\033[0m");
          char var[200];
          fscanf((FILE *)data_file, "%s", var);
          printf("%s\n", var);
        } else if (strcmp(buff, basic_command[EXIT]) == 0) {
          printf("%sEXIT exist%s\n", "\033[1;34m", "\033[0m");
        }
      }
    }
  }

  fclose(data_file);
}

/* Read */
void read_param(FILE *data_file) {
  printf("%sParams exist%s\n", "\033[1;34m", "\033[0m");
  char var[200];
  fscanf((FILE *)data_file, "%s", var);
  printf("%s\n", var);
}
void read_variable(FILE *data_file) {
  printf("%sVariables exist%s\n", "\033[1;34m", "\033[0m");
  char var[200];
  fscanf((FILE *)data_file, "%s", var);
  printf("%s\n", var);
}
void read_constant(FILE *data_file) {
  printf("%sConstant exist%s\n", "\033[1;34m", "\033[0m");
  char var[200];
  fscanf((FILE *)data_file, "%s", var);
  printf("%s\n", var);
}
/* Read */

/* Make */
void make_param(char *name, char *type) {
  printf("\nCreate param %s with type %s\n", name, type);
}
void make_variable(char *name, char *type) {
  printf("\nCreate variable %s with type %s\n", name, type);
}
void make_constant(char *name, char *type) {
  printf("\nCreate constant %s with type %s\n", name, type);
}
/* Make */