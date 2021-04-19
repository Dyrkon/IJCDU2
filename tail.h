// tail.h
// Řešení IJC-DU2, příklad a), 19.4.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Hlavička k implementaci tail

#ifndef IJCDU2_TO_BE_TESTEDC_H
#define IJCDU2_TO_BE_TESTEDC_H

#include "string.h"

// Tail

typedef struct input {
    char **lines;
    long line_number;
    long lines_allocated;
    bool error_occurred;
}input_t;

void usage();

int start_tail(int argc, char **argv);

int do_tail(char *filename, char *to_print, bool is_file);

int alloc_lines(bool do_realloc, input_t *input, size_t n);

int read_from_file(input_t *input, FILE *fp);

int read_from_stdin(input_t *input);

input_t get_input(char *filename, bool is_file);

void free_all(input_t *input);

#endif //IJCDU2_TO_BE_TESTEDC_H
