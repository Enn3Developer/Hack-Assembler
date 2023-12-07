#include "file.h"
#include <stdio.h>

file_t read_file(char *filename) {
    char buffer[80];
    string_t content = new_string(64);
    FILE *fin = fopen(filename, "r");

    while (fgets(buffer, 80, fin) != NULL) {
        append(&content, buffer);
    }

    fclose(fin);

    file_t file = {content, 0};
    return file;
}

void read_line(file_t *file, string_t *line) {
    *line = new_string(8);
    unsigned long index = file->pointer;
    if (index >= file->content.len) {
        return;
    }
    char c = file->content.elements[index];

    while (c != '\n' && index < file->content.len) {
        push(line, c);

        index++;
        c = file->content.elements[index];
    }
    index++;

    file->pointer = index;
}

void write_file(char *filename, char *content) {
    FILE *fout = fopen(filename, "w");
    fputs(content, fout);
    fclose(fout);
}