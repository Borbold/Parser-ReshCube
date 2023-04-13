#include "parser.h"

#include "stdint.h"
#include "stdio.h"
#include "string.h"

#define DATA_FILE "./test/tests_scripts.txt"

void main() {
  FILE *data_file = fopen(DATA_FILE, "r");
  char buff[64];
  int basic_count = 0, out_count = 0;
  while (fscanf((FILE *)data_file, "%s", buff) != EOF) {
    if (strcmp(buff, basic_command[basic_count]) == 0) {
      if (strcmp(buff, basic_command[PROGRAM]) == 0) {
        printf("%sPROGRAM exist%s\n", "\033[1;34m", "\033[0m");
      } else if (strcmp(buff, basic_command[PARAMS]) == 0) {
        printf("%sParams exist%s\n", "\033[1;34m", "\033[0m");
        char var[200];
        fscanf((FILE *)data_file, "%s", var);
        printf("%s\n", var);
      } else if (strcmp(buff, basic_command[VARIABLES]) == 0) {
        printf("%sVariables exist%s\n", "\033[1;34m", "\033[0m");
        char var[200];
        fscanf((FILE *)data_file, "%s", var);
        printf("%s\n", var);
      } else if (strcmp(buff, basic_command[START_TIME]) == 0) {
        printf("%sStart time exist%s\n", "\033[1;34m", "\033[0m");
        char var[200];
        fscanf((FILE *)data_file, "%s", var);
        printf("%s\n", var);
      } else if (strcmp(buff, basic_command[CONSTANT]) == 0) {
        printf("%sConstant exist%s\n", "\033[1;34m", "\033[0m");
        char var[200];
        fscanf((FILE *)data_file, "%s", var);
        printf("%s\n", var);
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
        printf("%sWAIT exist%s\n", "\033[1;34m", "\033[0m");
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
      if (++basic_count == sizeof(basic_command) / sizeof(basic_command[0]) - 1)
        break;
    }
  }

  fclose(data_file);
}