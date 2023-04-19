#ifndef TYPES_H
#define TYPES_H

#include "ref.h"

typedef struct {
  char *name;
  attribute_type type;
  union {
    int integer;
    float decimal;
    char *string;
  } val;
} attribute;

typedef struct {
  char *name;
  state_type type;
  attribute *attribute;
  int num_attr;
} parser_state;

typedef struct {
  int number_line;
  char *name;
  result_type type;
  attribute *attribute;
  int num_attr;
} parser_result;

#endif