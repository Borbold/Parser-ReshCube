#include "result_parcer.h"

#include "../basic_parser.h"

parser_result *read_string(parser_init *struct_init, int number_line) {
  FILE *file = struct_init->file;
  fseek(file, 1, SEEK_SET);

  parser_result *struct_result = malloc(sizeof(parser_result));

  char *buff, r_b;
  int count_line = 0, read_count = 0;
  while (fread(&r_b, 1, 1, file) > 0) {
    printf("\nHello\n");
    if (count_line == number_line) {
      if (not_comment(file, r_b) == 0)
        buff = get_word(r_b, buff, &read_count);
    }
    if (r_b == '\n') {
      count_line++;
    }
  }

  return struct_result;
}

void free_result(parser_result *par) {
  for (int i = 0; i < par->operation_num; i++)
    free(par[i].operation_list);
  free(par->operation_list);
  free(par);
}