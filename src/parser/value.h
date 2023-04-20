#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

typedef enum {
  VALUE_EXACLY,
  VALUE_CONSTANT,
  VALUE_NULL,
} value_type;

typedef struct {
  char *name;
  value_type type;
} value;

#endif