#include <stdio.h>
#include "file.h"
#include "preproccesor.h"

int main(int argc, char **argv) {
    if (argc >= 2) {
        file_t file = read_file(argv[1]);
        variables_t vars = new_variables();
        variables_add_std_vars(&vars);
        string_t preprocessed = preprocess(&file, &vars);
        for (unsigned int i = 0; i < preprocessed.len; i++) {
            printf("%c", preprocessed.elements[i]);
        }
    }

    return 0;
}
