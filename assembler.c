#include "assembler.h"
#include <stdlib.h>
#include <memory.h>

string_t assemble(string_t *preprocessed, variables_t *vars) {
    string_t ass = new_string(256);
    string_t line;

    for (unsigned int i = 0; i < preprocessed->len; i++) {
        char c = preprocessed->elements[i];

        switch (c) {
            case '\n': // newlines
                push(&ass, c);
                break;
            case '@': // A-instructions
                line = substring_to_newline(preprocessed, i + 1);
                i += line.len;
                string_t a_i = a_inst(&line, vars);
                append_str(&ass, &a_i);
                break;
            default: // C-instructions
                line = substring_to_newline(preprocessed, i + 1);
                i += line.len;
                string_t c_i = c_inst(&line, vars);
                append_str(&ass, &c_i);
                break;
        }
    }

    return ass;
}

string_t a_inst(string_t *line, variables_t *vars) {
    if (line->elements[0] >= '0' && line->elements[0] <= '9') {
        char *str = malloc(sizeof(char) * line->len);
        memcpy(str, line->elements, line->len);
        unsigned int value = atoi(str);
        free(str);
        return to_binary(value);
    } else {
        unsigned int var = variables_find(vars, *line);
        return to_binary(var);
    }
}

string_t c_inst(string_t *line, variables_t *vars) {
    string_t c_i = new_string(16);
    append(&c_i, "111");
    push(&c_i, '0' + (contains(line, 'M') >= 0));

    int d[3];
    d[0] = 0;
    d[1] = 0;
    d[2] = 0;

    int j[3];
    j[0] = 0;
    j[1] = 0;
    j[2] = 0;

    int equal_pos = contains(line, '=');
    int jmp_pos = contains(line, ';');
    int comp_pos = 1;

    switch (line->elements[equal_pos + comp_pos]) {
        case '0':
            append(&c_i, "101010");
            break;
        case '1':
            append(&c_i, "111111");
            break;
        case '-':
            switch (line->elements[equal_pos + comp_pos + 1]) {
                case '1':
                    append(&c_i, "111010");
                    break;
                case 'D':
                    append(&c_i, "001111");
                    break;
                case 'A':
                case 'M':
                    append(&c_i, "110011");
                    break;
            }
            break;
        case '!':
            switch (line->elements[equal_pos + comp_pos + 1]) {
                case 'D':
                    append(&c_i, "001101");
                    break;
                case 'A':
                case 'M':
                    append(&c_i, "110001");
                    break;
            }
            break;
        case 'D':
            if (equal_pos + comp_pos + 1 == line->len || line->elements[equal_pos + comp_pos + 1] == ';') {
                append(&c_i, "001100");
            } else {
                switch (line->elements[equal_pos + comp_pos + 1]) {
                    case '&':
                        append(&c_i, "000000");
                        break;
                    case '|':
                        append(&c_i, "010101");
                        break;
                    case '+':
                        if (line->elements[equal_pos + comp_pos + 2] == '1') {
                            append(&c_i, "011111");
                        } else {
                            append(&c_i, "000010");
                        }
                        break;
                    case '-':
                        if (line->elements[equal_pos + comp_pos + 2] == '1') {
                            append(&c_i, "001110");
                        } else {
                            append(&c_i, "010011");
                        }
                        break;
                }
            }
            break;
        case 'A':
        case 'M':
            if (equal_pos + comp_pos + 1 == line->len || line->elements[equal_pos + comp_pos + 1] == ';') {
                append(&c_i, "110000");
            } else {
                switch (line->elements[equal_pos + comp_pos + 1]) {
                    case '+':
                        append(&c_i, "110111");
                        break;
                    case '-':
                        if (line->elements[equal_pos + comp_pos + 2] == '1') {
                            append(&c_i, "110010");
                        } else {
                            append(&c_i, "000111");
                        }
                        break;
                }
            }
            break;
    }

    if (equal_pos >= 0) {
        // TODO: manage dest (update equal_pos)
    }

    if (jmp_pos >= 0) {
        // TODO: manage jumps
    }
}

string_t to_binary(unsigned int n) {
    int num_bits = 16;

    char *string = malloc(num_bits);
    string[0] = '0';
    for (int i = num_bits - 1; i >= 1; i--) {
        string[i] = (n & 1) + '0';
        n >>= 1;
    }

    return from(string);
}