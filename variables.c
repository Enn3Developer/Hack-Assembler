#include "variables.h"
#include <stdlib.h>

var_entry_t new_var_entry(string_t key, unsigned int value) {
    var_entry_t v = {key, value};
    return v;
}

var_dict_t new_var_dict(unsigned long capacity) {
    unsigned long len = 0;
    var_entry_t *elements = malloc(capacity * sizeof(var_entry_t));
    var_dict_t v = {elements, len, capacity};
    return v;
}

void var_dict_add(var_dict_t *dict, string_t key, unsigned int value) {
    if (dict->len == dict->capacity) {
        unsigned long c = dict->capacity << 1;
        var_entry_t *tmp = malloc(c * sizeof(var_entry_t));
        free(dict->elements);
        dict->elements = tmp;
        dict->capacity = c;
    }

    dict->elements[dict->len] = new_var_entry(key, value);
    dict->len++;
}

unsigned int var_dict_find(var_dict_t *dict, string_t key) {
    for (unsigned int i = 0; i < dict->len; i++) {
        var_entry_t entry = dict->elements[i];
        if (equals(&entry.key, &key)) {
            return entry.value;
        }
    }

    return 0;
}

variables_t new_variables() {
    variables_t vars = {new_var_dict(8), new_var_dict(8)};
    return vars;
}

void variables_push_var(variables_t *variables, string_t var) {
    unsigned int pointer = variables->variables.len + 16;
    for (unsigned int i = 0; i < variables->variables.len; i++) {
        var_entry_t entry = variables->variables.elements[i];
        if (equals(&entry.key, &var)) {
            return;
        }
    }
    var_dict_add(&variables->variables, var, pointer);
}

void variables_add_variable(variables_t *variables, string_t var, unsigned int value) {
    for (unsigned int i = 0; i < variables->variables.len; i++) {
        var_entry_t entry = variables->variables.elements[i];
        if (equals(&entry.key, &var)) {
            return;
        }
    }
    var_dict_add(&variables->labels, var, value);
}

void variables_add_label(variables_t *variables, string_t label, unsigned int value) {
    for (unsigned int i = 0; i < variables->labels.len; i++) {
        var_entry_t entry = variables->labels.elements[i];
        if (equals(&entry.key, &label)) {
            entry.value = value;
            return;
        }
    }
    var_dict_add(&variables->labels, label, value);
}

unsigned int variables_find(variables_t *variables, string_t key) {
    for (unsigned int i = 0; i < variables->labels.len; i++) {
        var_entry_t entry = variables->labels.elements[i];
        if (equals(&entry.key, &key)) {
            return entry.value;
        }
    }

    for (unsigned int i = 0; i < variables->variables.len; i++) {
        var_entry_t entry = variables->variables.elements[i];
        if (equals(&entry.key, &key)) {
            return entry.value;
        }
    }

    return 0;
}

void variables_add_std_vars(variables_t *variables) {
    variables_add_variable(variables, from("R0"), 0);
    variables_add_variable(variables, from("R1"), 1);
    variables_add_variable(variables, from("R2"), 2);
    variables_add_variable(variables, from("R3"), 3);
    variables_add_variable(variables, from("R4"), 4);
    variables_add_variable(variables, from("R5"), 5);
    variables_add_variable(variables, from("R6"), 6);
    variables_add_variable(variables, from("R7"), 7);
    variables_add_variable(variables, from("R8"), 8);
    variables_add_variable(variables, from("R9"), 9);
    variables_add_variable(variables, from("R10"), 10);
    variables_add_variable(variables, from("R11"), 11);
    variables_add_variable(variables, from("R12"), 12);
    variables_add_variable(variables, from("R13"), 13);
    variables_add_variable(variables, from("R14"), 14);
    variables_add_variable(variables, from("R15"), 15);

    variables_add_variable(variables, from("SCREEN"), 16384);
    variables_add_variable(variables, from("KBD"), 24576);

    variables_add_variable(variables, from("SP"), 0);
    variables_add_variable(variables, from("LCL"), 1);
    variables_add_variable(variables, from("ARG"), 2);
    variables_add_variable(variables, from("THIS"), 3);
    variables_add_variable(variables, from("THAT"), 4);
}