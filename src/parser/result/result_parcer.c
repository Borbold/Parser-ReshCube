#include "result_parcer.h"

#include "../basic_parser.h"

parser_result *read_string(parser_init *struct_init, int number_line) {
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
  printf("%s\n", buff);

  free(buff);
  fclose(file);
  return struct_result;
}

void free_result(parser_result *par) {
  for (int i = 0; i < par->operation_num; i++)
    free(par[i].operation_list);
  free(par->operation_list);
  free(par);
}