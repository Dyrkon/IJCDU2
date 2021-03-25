// tail.c
// Řešení IJC-DU2, příklad a), 24.3.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Výpis posledních n řádků souboru nebo standartního vstupu

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINES 511

void usage()
{
    printf(
           "Usage:\n"
           " tail YOUR-FILE\n"
           " tail -n (+/-)NUMBER-OF-LINES-TO-PRINT YOUR-FILE\n"
           " tail -n (+/-)NUMBER-OF-LINES-TO-PRINT < YOUR-FILE\n");
}

char *get_input(unsigned int max_line, char *filename, bool is_file)
{
    if (is_file)
    {
        FILE *fp;
        char *input;

        if ((fp = fopen(filename, "r")) == NULL)
        {
            fprintf(stderr, "Unable to open file!");
            fclose(fp);
            return NULL;
        }

        if ((input = calloc(511, sizeof(char))) == NULL)
        {
            fprintf(stderr, "Unable to allocate enough memory!");
            fclose(fp);
            return NULL;
        }

        if (!fscanf(fp,"%s", input))
        {
            fprintf(stderr, "Unable to read input!");
            fclose(fp);
            return NULL;
        }

        // Check if its the files end.

        fclose(fp);
    }
    else
    {
        // Stdin
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        const char *filename = argv[1];
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "-n"))
        {
            printf("Wrong parameters given!\n");
            usage();
        }
        else
        {
            char *end;
            long number_of_lines = strtol(argv[2],&end, 10);

        }
    }
    else if (argc == 4)
    {

    }
    else
    {
        printf("Too few parameters supplied!\n");
        usage();
        return 0;
    }

    return 0;
}
