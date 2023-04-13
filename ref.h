#ifndef REF_H
#define REF_H

/* This is used to determine the attribute types. */
typedef enum {
  INT,     /**< The database's integer type. */
  STRING,  /**< The database's ASCII string / char type. */
  DECIMAL, /**< The database's decimal type. */
} attr_type;

typedef enum {
    VARIABLE,
    PARAM,
    CONSTANT,
} param_type;

/* Type size references */
static const int SIZE_BYTE = sizeof(char);

#endif