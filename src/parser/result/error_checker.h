#ifndef ERROR_CHECKER_H
#define ERROR_CHECKER_H

#include "result_parcer.h"

int check_error_all_miss_mirror_symbol(parser_result *struct_result,
                                       char *check_str);
int check_error_long_line(parser_result *struct_result, int i,
                          char *string_line);

#endif