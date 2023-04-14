#ifndef TYPES_H
#define TYPES_H

#include "ref.h"

typedef struct {
  char *name;
  str_type type;
  struct {
    char *name;
    attr_type type;
    union {
      int integer;
      float decimal;
      char *string;
    } val;
  } attr;
  int offset;
  int length;
} basic_attr;

#endif