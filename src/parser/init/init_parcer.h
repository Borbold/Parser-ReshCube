#ifndef INIT_parser_H
#define INIT_parser_H

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "../value.h"

typedef enum {
  INIT_VAR,
  INIT_CON,
  INIT_ERR,
} init_type;

typedef struct {
  char *name;
  char *type;
} argument_list;

typedef struct {
  init_type init_type;
  char *name;
  uint8_t arg_num;
  argument_list *arg_list;
  FILE *file;
} parser_init;

parser_init *init_parser(char *path);
void free_init(parser_init *par);

#endif