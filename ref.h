#ifndef REF_H
#define REF_H

/* This is used to determine the attribute types. */
typedef enum {
  INT, /**< The database's integer type. */
  DEC, /**< The database's decimal type. */
  STR, /**< The database's ASCII string / char type. */
} attr_type;

typedef enum {
  VAR,
  CON,
  ERR_H,
  NUL_H,
} head_type;

typedef enum {
  FUN,
  TAG,
  ERR_B,
  NUL_B,
} body_type;

/* Type size references */
static const int SIZE_BYTE = sizeof(char);

#endif