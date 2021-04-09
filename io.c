#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htab.h"

int read_word(char *s, int max, FILE *f)
{
    int length = 0;
    int character = 0;
    char *temp_word = NULL;

    if ((temp_word = malloc(max * sizeof(char))) != NULL)
    {
        for (; length < max-1; length++)
        {
            character = fgetc(f);
            if (character != ' ' && character != EOF)
                temp_word[length] = character;
            else
                break;
        }

        // TODO
        if (length > 1 && character != EOF)
        {
            if ((s = malloc((length+1) * sizeof(char))) == NULL)
            {
                free(temp_word);
                return EOF;
            }
            temp_word[length+1] = '\0';
            strcpy(s, temp_word);
            free(temp_word);
            printf("%s", s);
            return length;
        }
    }
    return EOF;
}
