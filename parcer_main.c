#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "src/parcer/init/init_parcer.h"
#include "src/parcer/result/result_parcer.h"

#define DATA_FILE "./test/tests_scripts.txt"

void main() { parser_init *struct_init = init_parser(DATA_FILE); }