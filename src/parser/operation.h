#ifndef OPERATION_H
#define OPERATION_H

#include "value.h"

typedef enum {
  OP_GTE,  // >=
  OP_GT,   // >
  OP_LTE,  // <=
  OP_LT,   // <
  OP_EQ,   // ==
  OP_NEQ,  // !=
  OP_ADD,  // +
  OP_SUB,  // -
  OP_MULT, // *
  OP_DIV,  // /
  OP_NOT,  // !
  OP_AND,  // &&
  OP_OR,   // ||
  OP_LP,   // (
  OP_RP,   // )
  OP_NULL  // Пустая
} operation_type;

typedef struct _operation {
  operation_type operation_type;
  value operand;
  struct _operation *next_operation;
} operation;

#endif