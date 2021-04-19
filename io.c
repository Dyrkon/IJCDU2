// io.c
// Řešení IJC-DU2, příklad b), 19.4.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Metody pro načítání zadaného souboru po slovech

#include "io.h"

void clear(char *s, int max)
{
    for(int i = 0; i <= max; ++i)
        s[i] = 0;
}

int read_word(char *s, int max, FILE *f)
{
    int length = 0;
    int character = 0;
    clear(s, max);
    while (length < max)
    {
        character = fgetc(f);
        if (character == EOF && length == 0)
            return -1;
        if (character > 32 && !isspace(character))
        {
            s[length] = (char)character;
            length++;
        }
        else if (isspace(character))
        {
            s[length+1] = '\0';
            break;
        }
    }

    if (!isspace(character))
    {
        while (true) {
            character = fgetc(f);
            if (character == EOF || isspace(character))
                break;
        }
        s[max] = -1;
        return length;
    }

    return length;
}
