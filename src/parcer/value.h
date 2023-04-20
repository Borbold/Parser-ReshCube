#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#define MAX_LEN 255

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