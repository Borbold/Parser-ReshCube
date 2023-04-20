#ifndef PARSER_H
#define PARSER_H

typedef enum { PROGRAM, VARIABLES, CONSTANT, STEPS } basic_string;

const char *const basic_command[] = {"program", "variables", "constant",
                                     "steps", 0};

#endif