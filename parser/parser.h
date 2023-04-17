#ifndef PARSER_H
#define PARSER_H

typedef enum { PROGRAM, VARIABLES, CONSTANT, STEPS, EXIT } basic_string;

const char *const basic_command[] = {
    "program:", "variables:", "constant:", "steps:", "exit:", 0};

#endif