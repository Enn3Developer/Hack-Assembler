#ifndef PROGETTO5_STRING_H
#define PROGETTO5_STRING_H

typedef struct string {
    char *elements;
    unsigned long len;
    unsigned long capacity;
} string_t;

string_t new_string(unsigned long capacity);

string_t from(const char *str);

void push(string_t *str, char element);

char pop(string_t *str);

void append(string_t *str, const char *elements);

void append_str(string_t *str, string_t *other);

void dealloc(string_t *str);

int equals(string_t *str, string_t *other);

void clear(string_t *str, unsigned long capacity);

#endif //PROGETTO5_STRING_H
