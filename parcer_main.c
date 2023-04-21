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
}