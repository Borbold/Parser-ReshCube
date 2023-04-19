#ifndef REF_H
#define REF_H

/* This is used to determine the attribute types. */
typedef enum {
  INT, /**< The database's integer type. */
  DEC, /**< The database's decimal type. */
  STR, /**< The database's ASCII string / char type. */
} attribute_type;

typedef enum {
  NAME,
  CON_A,
  NUL_A,
} parse_attr_type;

typedef enum {
  VAR,
  CON,
  ERR_H,
  NUL_H,
} state_type;

typedef enum {
  FUN,
  ERR_B,
  NUL_B,
} result_type;

/* Type size references */
static const int SIZE_BYTE = sizeof(char);

#endif