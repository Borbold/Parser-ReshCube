#ifndef RESULT_PARSER_H
#define RESULT_PARSER_H

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
  char *err_str;
  result_type result_type;
  char *name;
  uint8_t attribute_num;
  operation *operation_list;
} parser_result;

parser_result *read_string(parser_state *struct_init);
void free_result(parser_result *par);
void set_fposition(FILE *file, fpos_t pos);
fpos_t get_fposition(FILE *file, fpos_t pos);

#endif