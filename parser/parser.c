#include "parser.h"

#include "stdint.h"
#include "stdio.h"
#include "string.h"

#define DATA_FILE "./test/tests_scripts.txt"

void main() {
  FILE *data_file = fopen(DATA_FILE, "r");
  char buff[64];
  int basic_count = 0;
  while (fscanf((FILE *)data_file, "%s", buff) != EOF) {
    if (strcmp(buff, basic_command[basic_count]) == 0) {
      printf("%s\n", buff);
      if (++basic_count == sizeof(basic_command) / sizeof(basic_command[0]) - 1)
        break;
    }
  }

  fclose(data_file);
}