#include "result_parcer.h"

#include "../basic_parser.h"

parser_result *read_string(parser_state *struct_init, int number_line) {
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

  int flag_N = 1;
  char *r_name = malloc(strlen(buff));
  int flag_V = 0;
  char *r_value = malloc(strlen(buff));

  int num_arg = 0;
  for (int i = 0, j = 0; i < strlen(buff); i++, j++) {
    if (flag_N) {
      if (buff[i] == ':') {
        flag_N = 0;
        flag_V = 1;
        j = 0;
        i++;
      } else
        r_name[j] = buff[i];
    }
    if (buff[i] == '[' || buff[i] == ',') {
      num_arg++;
    }
    if (flag_V) {
      r_value[j] = buff[i];
    }
  }

  struct_result->result_type = RESULT_FUN;
  struct_result->attribute_num = num_arg;
  struct_result->name = r_name;
  struct_result->operation_list = malloc(num_arg * sizeof(operation));
  for (int i = 0; i < num_arg; i++)
    struct_result->operation_list[i].operand.name = malloc(sizeof(char));

  int i = 1;
  for (int j = 0; j < num_arg; j++) {
    for (int k = 0; i < strlen(r_value) - 1; i++, k++) {
      if (r_value[i] == ',') {
        i++;
        break;
      }
      struct_result->operation_list[j].operand.name[k] = r_value[i];
    }
  }

  printf("%s count:%d\n", struct_result->name, struct_result->attribute_num);
  for (int i = 0; i < num_arg; i++)
    printf("%s\n", struct_result->operation_list[i].operand.name);

  free(buff);
  fclose(file);
  return struct_result;
}

void free_result(parser_result *par) {
  for (int i = 0; i < par->attribute_num; i++)
    free(par[i].operation_list);
  free(par->operation_list);
  free(par);
}