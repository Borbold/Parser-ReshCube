#ifndef INIT_PARSER_H
#define INIT_PARSER_H

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "../value.h"

typedef enum {
  INTEGER,
  DECIMALE,
  STRING,
} variable_type;

typedef struct {
  char *name;
  variable_type type;
  void *value;
} variable_list;

typedef struct {
  char *name;
  char *value;
} constant_list;

typedef struct {
  fpos_t state_pos;
  fpos_t current_pos;
  char *err_str;
  uint8_t val_num;
  variable_list *var_list;
  uint8_t con_num;
  constant_list *con_list;
  FILE *file;
} parser_state;

parser_state *init_parser(char *path);
void free_init(parser_state *par);

#endif