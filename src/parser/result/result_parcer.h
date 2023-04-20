#ifndef RESULT_parser_H
#define RESULT_parser_H

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "../init/init_parcer.h"
#include "../operation.h"

typedef enum {
  RESULT_FUN,
  RESULT_ERR,
} result_type;

typedef struct {
  result_type result_type;
  char *name;
  uint8_t operation_num;
  operation *operation_list;
} parser_result;

parser_result *read_string(parser_init *struct_init, int number_line);
void free_result(parser_result *par);

#endif