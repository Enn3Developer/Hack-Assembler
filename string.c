#include "string.h"
#include <stdlib.h>
#include <memory.h>

string_t new_string(unsigned long capacity) {
    unsigned long len = 0;
    char *elements = malloc(capacity * sizeof(char));
    string_t array = {elements, len, capacity};
    return array;
}

string_t from(const char *chars) {
    string_t str = new_string(1);
    append(&str, chars);

    return str;
}

void push(string_t *str, char element) {
    if (str->len == str->capacity) {
        unsigned long c = str->capacity << 1;
        char *tmp = malloc(c * sizeof(char));
        memcpy(tmp, str->elements, str->len * sizeof(char));
        free(str->elements);
        str->elements = tmp;
        str->capacity = c;
    }
    str->elements[str->len] = element;
    str->len++;
}

char pop(string_t *str) {
    if (str->len == 0) {
        return 0;
    }
    str->len--;
    char last = str->elements[str->len];
    return last;
}

void append(string_t *str, const char *elements) {
    char c = elements[0];
    unsigned long index = 0;

    while (c != '\0') {
        push(str, c);
        index++;
        c = elements[index];
    }
}

void append_str(string_t *str, string_t *other) {
    if (other->len == 0) {
        return;
    }

    if ((str->len + other->len) >= str->capacity) {
        unsigned long c = str->capacity << 1;
        char *tmp = malloc(c * sizeof(char));
        memcpy(tmp, str->elements, str->len * sizeof(char));
        free(str->elements);
        str->elements = tmp;
        str->capacity = c;
    }

    memcpy(str->elements + str->len, other->elements, other->len);
//    for (unsigned int i = 0; i < other->len; i++) {
//        str->elements[str->len + i] = other->elements[i];
//    }
    str->len += other->len;
}

void dealloc(string_t *str) {
    free(str->elements);
}

int equals(string_t *str, string_t *other) {
    if (str->len != other->len) {
        return 0;
    }

    for (unsigned int i = 0; i < str->len; i++) {
        if (str->elements[i] != other->elements[i]) {
            return 0;
        }
    }

    return 1;
}

void clear(string_t *str, unsigned long capacity) {
    str->len = 0;
    char *tmp = malloc(capacity * sizeof(char));
    free(str->elements);
    str->elements = tmp;
    str->capacity = capacity;
}

string_t substring_to_newline(string_t *str, unsigned int idx) {
    string_t s = new_string(8);
    unsigned int i = idx;
    char c = str->elements[i];

    while (c != '\n') {
        push(&s, c);
        i++;
        c = str->elements[i];
    }

    return s;
}

int contains(string_t *str, char c) {
    for (unsigned int i = 0; i < str->len; i++) {
        if (str->elements[i] == c) {
            return i;
        }
    }

    return -1;
}

int substring_equals(string_t *str, unsigned int start, unsigned int len, const char *chars) {
    if (str->len <= (start + len)) {
        return 0;
    }

    for (unsigned int i = start; i < (start + len); i++) {
        if (str->elements[i] != chars[i - start]) {
            return 0;
        }
    }

    return 1;
}

char *substring(string_t *str, unsigned int start, unsigned int len) {
    char *chars = malloc(sizeof(char) * (len + 1));

    if (str->len < (start + len)) {
        return chars;
    }

    for (unsigned int i = start; i < (start + len); i++) {
        chars[i - start] = str->elements[i];
    }

    chars[len] = '\0';

    return chars;
}

string_t copy(string_t *str) {
    string_t new = new_string(str->capacity);
    append_str(&new, str);

    return new;
}