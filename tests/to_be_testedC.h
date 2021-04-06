#ifndef IJCDU2_TO_BE_TESTEDC_H
#define IJCDU2_TO_BE_TESTEDC_H

#include "string.h"

// Tail

typedef struct input {
    char **lines;
    long line_number;
    long lines_allocated;
}input_t;

int start_tail(int argc, char **argv);

void free_all(input_t *input);

input_t get_input(char *filename, bool is_file);

int read_from_stdin(input_t *input);

int read_from_file(input_t *input, FILE *fp);

int alloc_lines(bool do_realloc, input_t *input, size_t n);

int do_tail(char *filename, char *to_print, bool is_file);

void usage();

// Word count model in C++


#endif //IJCDU2_TO_BE_TESTEDC_H
