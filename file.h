#ifndef PROGETTO5_FILE_H
#define PROGETTO5_FILE_H

#include "string.h"

typedef struct file {
    string_t content;
    unsigned long pointer;
} file_t;

file_t read_file(char *filename);

void read_line(file_t *file, string_t *line);

void write_file(char *filename, char *content);

#endif //PROGETTO5_FILE_H
