#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "src/parser/init/init_parcer.h"
#include "src/parser/result/result_parcer.h"

#define DATA_FILE "./test/tests_scripts.txt"

void main(int argc, char *argv[]) {
  parser_state *struct_init = init_parser(DATA_FILE);
  if (!struct_init->err_str) {
    set_fposition(struct_init->file, struct_init->state_pos);
    parser_result *struct_result;
    // Имитация чтения строк
    for (int i = 0; i < atoi(argv[1]); i++) {
      struct_result = read_string(struct_init);
      if (struct_result->err_str && strlen(struct_result->err_str) > 0) {
        printf("%s%s%s\n", "\033[1;31m", struct_result->err_str, "\033[0m");
        return;
      }
    }

    printf("\n\033[1;36m%s\t\t| count: %d\n", struct_result->name,
           struct_result->attribute_num);
    for (int i = 0; i < struct_result->attribute_num; i++) {
      if (struct_result->operation_list[i].operation_type == OP_NULL) {
        printf("%s\t| type: %d\n",
               struct_result->operation_list[i].operand.name,
               struct_result->operation_list[i].operand.type);
      } else {
        operation *op = &struct_result->operation_list[i];
        while (op != NULL) {
          printf("%s\t| OP_type:%d\n", op->operand.name, op->operation_type);
          op = op->next;
        }
      }
    }
  }
}