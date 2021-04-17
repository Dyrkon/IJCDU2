#include "io.h"

void clear(char *s)
{
    for(int i = 0; i < MAX_WORD; ++i)
        s[i] = 0;
}

// TODO(Varovani muze byt jen jedno????)
int read_word(char *s, int max, FILE *f)
{
    int length = 0;
    int character = 0;
    clear(s);
    for (; length < max-1; length++)
    {
        character = fgetc(f);
        if (character == EOF && length == 0)
            return -1;
        if (!isspace(character) && character != EOF)
        {
            s[length] = (char)character;
        }
        else
        {
            s[length+1] = '\0';
            break;
        }
    }
    if (isalpha(character))
    {
        fprintf(stderr, "Slovo bylo načteno jen z části");
        return -1;
    }

    return length;
}
