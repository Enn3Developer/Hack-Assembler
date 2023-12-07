#include "preproccesor.h"
#include "variables.h"
#include <stdio.h>
#include <stdlib.h>

string_t preprocess(file_t *file, variables_t *vars) {
    string_t line;
    string_t preprocessed = new_string(64);
    string_t processing = new_string(8);
    int is_processing = 0;
    unsigned int line_idx = 0;
    unsigned int line_labeled = 0;
    int no_new_line = 0;

    while (file->pointer < file->content.len) {
        read_line(file, &line);
        line_idx += 1;
        int spaced = 0;
        // skip line if empty
        if (line.len == 0) {
            continue;
        }

        for (int i = 0; i < line.len; ++i) {
            char c = line.elements[i];
            int break_for = 0;
            switch (c) {
                // deletes spaces and \r
                case '\t':
                case ' ':
                    spaced++;
                case '\r':
                    break;
                    // deletes comments
                case '/':
                    if (i < line.len - 1) {
                        if (line.elements[i + 1] == '/') {
                            break_for = 1;
                        } else {
                            printf("error! invalid expression found after @ at line %d\n",
                                   line_idx);
                            exit(1);
                        }
                    }
                    // if the comment is first in the line (not counting whitespaces)
                    no_new_line = !(i - spaced);
                    break;
                    // variables
                case '@':
                    is_processing = 1;
                    push(&preprocessed, c);
                    break;
                    // labels
                case '(':
                    is_processing = 1;
                    break;
                    // ending labels
                case ')':
                    is_processing = 0;
                    if (processing.len > 0) {
                        // if label starts with a digit then error
                        if (processing.elements[0] >= '0' && processing.elements[0] <= '9') {
                            printf("error! invalid label found at line %d (started with a digit)\n",
                                   line_idx);
                            exit(1);
                        } else {
                            variables_add_label(vars, processing, line_labeled);
                            clear(&processing, 8);
                        }
                    } else {
                        printf("error! no label found at line %d\n", line_idx);
                        exit(1);
                    }
                    no_new_line = 1;
                    break;
                default:
                    if (is_processing) {
                        push(&processing, c);
                    } else {
                        push(&preprocessed, c);
                    }
                    break;
            }

            if (break_for) {
                break;
            }
        }

        if (is_processing) {
            is_processing = 0;
            if (processing.len > 0) {
                // starts with a digit
                if (processing.elements[0] >= '0' && processing.elements[0] <= '9') {
                    // if the second character isn't a digit then error
                    if (processing.len >= 2 &&
                        !(processing.elements[1] >= '0' && processing.elements[1] <= '9')) {
                        printf("error! invalid variable found after @ at line %d (started with a digit)\n",
                               line_idx);
                        exit(1);
                    }
                } else {
                    variables_push_var(vars, processing);
                }
                append_str(&preprocessed, &processing);
                clear(&processing, 8);
            } else {
                printf("error! no value found after @ at line %d\n", line_idx);
                exit(1);
            }
        }

        if ((!no_new_line) && line.len > 1) {
            push(&preprocessed, '\n');
            line_labeled++;
        } else {
            no_new_line = 0;
        }
    }

    return preprocessed;
}