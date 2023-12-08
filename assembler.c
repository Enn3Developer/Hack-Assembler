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
                line = substring_to_newline(preprocessed, i);
                i += line.len - 1;
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

    int equal_pos = contains(line, '=');
    int jmp_pos = contains(line, ';');
    int comp_pos = 1;

    switch (line->elements[equal_pos + comp_pos]) {
        case '0':
            append(&c_i, "101010\0");
            break;
        case '1':
            append(&c_i, "111111\0");
            break;
        case '-':
            switch (line->elements[equal_pos + comp_pos + 1]) {
                case '1':
                    append(&c_i, "111010\0");
                    break;
                case 'D':
                    append(&c_i, "001111\0");
                    break;
                case 'A':
                case 'M':
                    append(&c_i, "110011\0");
                    break;
            }
            break;
        case '!':
            switch (line->elements[equal_pos + comp_pos + 1]) {
                case 'D':
                    append(&c_i, "001101\0");
                    break;
                case 'A':
                case 'M':
                    append(&c_i, "110001\0");
                    break;
            }
            break;
        case 'D':
            if (equal_pos + comp_pos + 1 == line->len || line->elements[equal_pos + comp_pos + 1] == ';') {
                append(&c_i, "001100\0");
            } else {
                switch (line->elements[equal_pos + comp_pos + 1]) {
                    case '&':
                        append(&c_i, "000000\0");
                        break;
                    case '|':
                        append(&c_i, "010101\0");
                        break;
                    case '+':
                        if (line->elements[equal_pos + comp_pos + 2] == '1') {
                            append(&c_i, "011111\0");
                        } else {
                            append(&c_i, "000010\0");
                        }
                        break;
                    case '-':
                        if (line->elements[equal_pos + comp_pos + 2] == '1') {
                            append(&c_i, "001110\0");
                        } else {
                            append(&c_i, "010011\0");
                        }
                        break;
                }
            }
            break;
        case 'A':
        case 'M':
            if (equal_pos + comp_pos + 1 == line->len || line->elements[equal_pos + comp_pos + 1] == ';') {
                append(&c_i, "110000\0");
            } else {
                switch (line->elements[equal_pos + comp_pos + 1]) {
                    case '+':
                        append(&c_i, "110111\0");
                        break;
                    case '-':
                        if (line->elements[equal_pos + comp_pos + 2] == '1') {
                            append(&c_i, "110010\0");
                        } else {
                            append(&c_i, "000111\0");
                        }
                        break;
                }
            }
            break;
    }

    if (equal_pos >= 0) {
        string_t sub = from(substring(line, 0, equal_pos));
        push(&c_i, '0' + (contains(&sub, 'A') >= 0));
        push(&c_i, '0' + (contains(&sub, 'D') >= 0));
        push(&c_i, '0' + (contains(&sub, 'M') >= 0));
    } else {
        append(&c_i, "000\0");
    }

    if (jmp_pos >= 0) {
        string_t sub = from(substring(line, jmp_pos + 1, line->len - jmp_pos - 1));
        string_t jmp = from("JMP");
        string_t jne = from("JNE");
        if (equals(&sub, &jmp)) {
            append(&c_i, "111\0");
        } else if (equals(&sub, &jne)) {
            append(&c_i, "101\0");
        } else {
            push(&c_i, '0' + (contains(&sub, 'L') >= 0));
            push(&c_i, '0' + (contains(&sub, 'E') >= 0));
            push(&c_i, '0' + (contains(&sub, 'G') >= 0));
        }
    } else {
        append(&c_i, "000\0");
    }

    return c_i;
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