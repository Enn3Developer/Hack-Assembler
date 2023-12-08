#ifndef PROGETTO5_ASSEMBLER_H
#define PROGETTO5_ASSEMBLER_H

#include "string.h"
#include "variables.h"

string_t assemble(string_t *preprocessed, variables_t *vars);

string_t a_inst(string_t *line, variables_t *vars);

string_t c_inst(string_t *line, variables_t *vars);

string_t to_binary(unsigned int value);

#endif //PROGETTO5_ASSEMBLER_H
