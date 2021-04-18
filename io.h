#ifndef IJCDU2_IO_H
#define IJCDU2_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD 127

// Čtení slov ze souboru
int read_word(char *s, int max, FILE *f);

#endif //IJCDU2_IO_H
