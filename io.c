#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htab.h"

int read_word(word_t *word, int max, FILE *f)
{
    word->length = 0;
    int character = 0;

    if ((word->s = malloc(max * sizeof(char))) != NULL)
    {
        for (; word->length < max-1; word->length++)
        {
            character = fgetc(f);
            if (character != ' ' && character != EOF)
                word->s[word->length] = character;
            else if (!strcmp(word->s, ""))
            {
                free(word->s);
                return EOF;
            } else
                break;
        }

        // TODO
        word->s[word->length+1] = '\0';
        return word->length;
    }
    return EOF;
}
