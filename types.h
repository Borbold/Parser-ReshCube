#ifndef TYPES_H
#define TYPES_H

#include "ref.h"

typedef struct {
    param_type type_param;
    struct {
        attr_type type;
        union {
          int integer;
          float decimal;
          char *string;
        }val;
    }attr;
} basic_attr;

#endif