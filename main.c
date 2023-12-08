#include <stdio.h>
#include "file.h"
#include "preproccesor.h"
#include "assembler.h"

int main(int argc, char **argv) {
    if (argc >= 2) {
        file_t file = read_file(argv[1]);
        variables_t vars = new_variables();
        variables_add_std_vars(&vars);
        string_t preprocessed = preprocess(&file, &vars);
        string_t assembled = assemble(&preprocessed, &vars);
        for (unsigned int i = 0; i < assembled.len; i++) {
            printf("%c", assembled.elements[i]);
        }
    }

    return 0;
}
