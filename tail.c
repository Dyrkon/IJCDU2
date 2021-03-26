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

typedef struct input {
    char **lines;
    long number_of_lines;
}input_t;

void usage()
{
    printf(
           "Usage:\n"
           " tail YOUR-FILE\n"
           " tail -n (+/-)NUMBER-OF-LINES-TO-PRINT YOUR-FILE\n"
           " tail -n (+/-)NUMBER-OF-LINES-TO-PRINT < YOUR-FILE\n");
}

int read_from_file(input_t *input, FILE *fp)
{
    int end_char = 0;
    while (end_char != EOF)
    {
        if ((input->lines[input->number_of_lines] = calloc(MAX_LINES+1, sizeof(char))) == NULL)
        {
            fprintf(stderr, "Unable to allocate enough memory!\n");
            fclose(fp);
            input->number_of_lines *= -1;
            return -1;
        }

        fscanf(fp,"%511s", input->lines[input->number_of_lines]);
        input->number_of_lines++;
        end_char = fgetc(fp);
        if (end_char != '\n')
        {
            fprintf(stderr, "Unable to read the full line.\n");
        }
    }
    return 0;
}

int read_from_stdin(input_t *input)
{
    int end_char = 0;
    while (end_char != EOF)
    {
        if ((input->lines[input->number_of_lines] = calloc(MAX_LINES+1, sizeof(char))) == NULL)
        {
            fprintf(stderr, "Unable to allocate enough memory!\n");
            input->number_of_lines *= -1;
            return -1;
        }

        scanf("%s",input->lines[input->number_of_lines]);
        input->number_of_lines++;
        end_char = getc(stdin);
        if (end_char != '\n')
        {
            fprintf(stderr, "Unable to read the full line.\n");
        }
    }
    return 0;
}

input_t get_input(char *filename, bool is_file)
{
    input_t  input;
    input.number_of_lines = 0;

    if (is_file)
    {
        FILE *fp;

        if ((fp = fopen(filename, "r")) == NULL) {
            fprintf(stderr, "Unable to open file!\n");
            fclose(fp);
            input.lines = NULL;
            return input;
        }

        if (read_from_file(&input,fp))
        {
            fprintf(stderr, "Unable to allocate enough memory!\n");
            fclose(fp);
            input.number_of_lines *= -1;
            return input;
        }

        fclose(fp);
        return input;
    }
    else
    {
        if (read_from_stdin(&input))
        {
            fprintf(stderr, "Unable to allocate enough memory!\n");
            input.number_of_lines *= -1;
            return input;
        }
    }
}

int main(int argc, char *argv[])
{
    input_t input;
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
            long lines_to_print = strtol(argv[2],&end, 10);
            input = get_input("",false);
            if (input.number_of_lines < 0)
            {
                for (int i = 0; i < input.number_of_lines*(-1); i++)
                {
                    free(input.lines[i]);
                }
            }
        }
    }
    else if (argc == 4)
    {
        if (strcmp(argv[1], "-n"))
        {
            printf("Wrong parameters given!\n");
            usage();
        }
        else
        {
            char *end;
            long lines_to_print = strtol(argv[2],&end, 10);
            input = get_input(argv[3],false);
            if (input.number_of_lines < 0)
            {
                for (int i = 0; i < input.number_of_lines*(-1); i++)
                {
                    free(input.lines[i]);
                }
            }
        }
    }
    else
    {
        printf("Too few parameters supplied!\n");
        usage();
        return 0;
    }

    return 0;
}
