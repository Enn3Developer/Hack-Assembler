#include <stdio.h>
#include "file.h"
#include "preproccesor.h"
#include "assembler.h"
#include <stdlib.h>
#include <memory.h>

int main(int argc, char **argv) {
    if (argc >= 2) {
        file_t file = read_file(argv[1]);
        variables_t vars = new_variables();
        variables_add_std_vars(&vars);
        string_t preprocessed = preprocess(&file, &vars);
        string_t assembled = assemble(&preprocessed, &vars);
        char *out = malloc(sizeof(char) * assembled.len + 1);
        memcpy(out, assembled.elements, assembled.len);
        out[assembled.len] = '\0';
        string_t filename = from(argv[1]);
        pop(&filename);
        pop(&filename);
        pop(&filename);
        append(&filename, "hack\0");
        char *name = malloc(sizeof(char) * filename.len + 1);
        memcpy(name, filename.elements, filename.len);
        name[filename.len] = '\0';
        write_file(name, out);
    }

    return 0;
}
