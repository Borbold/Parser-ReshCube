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
  str_type type;
  attr *attribute;
  int num_attr;
} basic_attr;

#endif