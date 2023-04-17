#ifndef TYPES_H
#define TYPES_H

#include "ref.h"

typedef struct {
  char *name;
  attr_type type;
  union {
    int integer;
    float decimal;
    char *string;
  } val;
} attr;

typedef struct {
  char *name;
  head_type type;
  attr *attribute;
  int num_attr;
} header_attr;

typedef struct {
  int number_line;
  char *name;
  body_type type;
  attr *attribute;
  int num_attr;
} body_attr;

#endif