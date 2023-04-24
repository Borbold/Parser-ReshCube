#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "src/parser/init/init_parcer.h"
#include "src/parser/result/result_parcer.h"

#define DATA_FILE "./test/tests_scripts.txt"

void main() {
  parser_state *struct_init = init_parser(DATA_FILE);
  parser_result *struct_result = read_string(struct_init, 28);

  printf("%s\t\t| count: %d\n", struct_result->name,
         struct_result->attribute_num);
  for (int i = 0; i < struct_result->attribute_num; i++) {
    if (struct_result->operation_list[i].operation_type == OP_NULL) {
      printf("%s\t| type: %d\n", struct_result->operation_list[i].operand.name,
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