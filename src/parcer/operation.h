#ifndef OPERATION_H
#define OPERATION_H

#include "value.h"

typedef enum {
  OPERATION_PLUS,
  OPERATION_MINUS,
  OPERATION_MULYIPLY,
  OPERATION_DIVISION,
  //...
} operation_type;

typedef struct _operation {
  operation_type oper_type;
  value operand;
  struct _operation *next_operation;
} operation;

#endif