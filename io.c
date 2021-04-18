#include "io.h"

void clear(char *s, int max)
{
    for(int i = 0; i <= max; ++i)
        s[i] = 0;
}

// TODO(Varovani muze byt jen jedno????)
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
        if (isalpha(character) && character > 32)
        {
            s[length] = (char)character;
            length++;
        }
        else if (strlen(s) != 0)
        {
            s[length+1] = '\0';
            break;
        }
    }

    if (isalpha(character))
    {
        while (!isspace((character = fgetc(f)))) {
            if (character == EOF) break;
        }
        s[max] = -1;
        return length;
    }

    return length;
}
