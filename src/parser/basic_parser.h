#ifndef BASIC_PARSER_H
#define BASIC_PARSER_H

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

#define MAX_LEN 255

int not_comment(FILE *file, char r_b);
char *get_word(char r_b, char *buff, int *read_count);
char *get_string(char r_b, FILE *file);

#endif