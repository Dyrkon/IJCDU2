// io.h
// Řešení IJC-DU2, příklad b), 19.4.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Hlavičkový soubor k io(načítání souborů)

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
