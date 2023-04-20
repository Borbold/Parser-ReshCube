#ifndef RESULT_PARCER_H
#define RESULT_PARCER_H

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "../operation.h"

typedef enum {
  RESULT_FUN,
  RESULT_ERR,
} result_type;

typedef struct {
  result_type init_type;
  char *name;
  uint8_t arg_num;
  operation *arg_list;
} parser_result;

void free_result(parser_result *par);

#endif