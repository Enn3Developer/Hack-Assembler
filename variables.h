#ifndef PROGETTO5_VARIABLES_H
#define PROGETTO5_VARIABLES_H

#include "string.h"

typedef struct var_entry {
    string_t key;
    unsigned int value;
} var_entry_t;

typedef struct var_dict {
    var_entry_t *elements;
    unsigned long len;
    unsigned long capacity;
} var_dict_t;

typedef struct variables {
    var_dict_t variables;
    var_dict_t labels;
} variables_t;

var_entry_t new_var_entry(string_t key, unsigned int value);

var_dict_t new_var_dict(unsigned long capacity);

void var_dict_add(var_dict_t *dict, string_t key, unsigned int value);

unsigned int var_dict_find(var_dict_t *dict, string_t key);

variables_t new_variables();

void variables_push_var(variables_t *variables, string_t var);

void variables_add_variable(variables_t *variables, string_t var, unsigned int value);

void variables_add_label(variables_t *variables, string_t label, unsigned int value);

int variables_find(variables_t *variables, string_t key);

void variables_add_std_vars(variables_t *variables);

#endif //PROGETTO5_VARIABLES_H