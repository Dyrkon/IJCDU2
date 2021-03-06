// tail.c
// Řešení IJC-DU2, příklad a), 24.3.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Výpis posledních n řádků souboru nebo standartního vstupu

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "tail.h"

#define MAX_LINES 511
#define MINIMAL_N_OF_LINES 5
#define ABS(x) ((x < 0) ? (x *= -1) : x)

int main(int argc, char *argv[])
{
    if (start_tail(argc, argv))
        return 1;
    else
        return 0;
}

void usage()
{
    printf(
            "Usage:\n"
            " tail YOUR-FILE\n"
            " tail -n (+/-)NUMBER-OF-LINES-TO-PRINT YOUR-FILE\n"
            " tail -n (+/-)NUMBER-OF-LINES-TO-PRINT < YOUR-FILE\n");
}

int start_tail(int argc, char *argv[])
{
    if (argc == 2)
    {
        if (argv[1])
            if (do_tail(argv[1], "|", true))
                return 1;
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "-n") != 0 || !isdigit(argv[2][0]))
        {
            printf("Wrong parameters given!\n");
            usage();
        }
        else
            if(do_tail(NULL, argv[2], false))
                return 1;
    }
    else if (argc == 4)
    {
        if (strcmp(argv[1], "-n") != 0)
        {
            printf("Wrong parameters given!\n");
            usage();
        }
        else
            if (do_tail(argv[3], argv[2], true))
                return 1;
    }
    else
    {
        printf("Too few parameters supplied!\n");
        usage();
    }
    return 0;
}

int do_tail(char *filename, char *to_print, bool is_file)
{
    input_t input;
    char *end;

    long lines_to_print;

    if (to_print[0] == '|')
        lines_to_print = 10;
    else
    {
        lines_to_print = strtol(to_print,&end, 10);
        ABS(lines_to_print);
    }

    input = get_input(!is_file ? "" : filename,is_file);

    if (input.line_number > 0 && input.lines != NULL)
    {
        if (lines_to_print > input.line_number)
            lines_to_print = input.line_number;
    }
    else
    {
        free_all(&input);
        return 1;
    }

    for (long i = input.line_number - lines_to_print; i < input.line_number; i++) {
        printf("%s\n", input.lines[i]);
    }

    free_all(&input);
    return 0;
}

int alloc_lines(bool do_realloc, input_t *input, size_t n)
{
    if (do_realloc)
    {
        char **temp = NULL;
        if ((temp = realloc(input->lines, (n + input->lines_allocated) * sizeof(char *))) == NULL)
        {
            fprintf(stderr, "Unable to reallocate enough memory!\n");
            return 1;
        }
        else
        {
            input->lines = temp;
            input->lines_allocated += n;
        }
    }
    else
    {
        if ((input->lines = calloc(n, sizeof(char *))) == NULL)
        {
            fprintf(stderr, "Unable to allocate enough memory!\n");
            return 1;
        }
        else
        {
            input->lines_allocated = MINIMAL_N_OF_LINES;
        }
    }
    return 0;
}

int read_from_file(input_t *input, FILE *fp)
{
    bool end_found = false;

    if (alloc_lines(false, input, MINIMAL_N_OF_LINES))
        return 1;

    while (!end_found)
    {
        if (input->lines_allocated == input->line_number)
        {
            if (input->line_number == input->lines_allocated) {
                if (alloc_lines(true, input, MINIMAL_N_OF_LINES))
                    return 1;
            }
        }
        else
        {
            int end_char;
            if ((input->lines[input->line_number] = calloc(MAX_LINES+1, sizeof(char))) == NULL) {
                fprintf(stderr, "Unable to allocate enough memory!\n");
                return 1;
            }

            fscanf(fp,"%511[^\n]s",input->lines[input->line_number]);
            input->line_number++;
            end_char = fgetc(fp);
            if (end_char == EOF)
                end_found = true;
            else if (end_char != '\n')
            {
                fscanf(fp, "%*[^\n]");
                end_char = fgetc(fp);
                input->error_occurred = true;
            }
        }
    }
    return 0;
}

int read_from_stdin(input_t *input)
{
    bool end_found = false;

    if (alloc_lines(false, input, MINIMAL_N_OF_LINES))
        return 1;

    while (!end_found)
    {
        if (input->lines_allocated == input->line_number)
        {
            if (input->line_number == input->lines_allocated) {
                if (alloc_lines(true, input, MINIMAL_N_OF_LINES))
                    return 1;
            }
        }
        else
        {
            int end_char;
            if ((input->lines[input->line_number] = malloc(MAX_LINES+1 * sizeof(char))) == NULL) {
                fprintf(stderr, "Unable to allocate enough memory!\n");
                return 1;
            }

            fscanf(stdin,"%511[^\n]s",input->lines[input->line_number]);
            input->line_number++;
            end_char = fgetc(stdin);
            if (end_char == EOF)
                end_found = true;
            else if (end_char != '\n')
            {
                fscanf(stdin, "%*[^\n]");
                end_char = fgetc(stdin);
                input->error_occurred = true;
            }
        }
    }
    return 0;
}

input_t get_input(char *filename, bool is_file)
{
    input_t  input;
    input.line_number = 0;
    input.lines_allocated = 0;
    input.error_occurred = false;

    if (is_file)
    {
        FILE *fp;

        if ((fp = fopen(filename, "r")) == NULL) {
            fprintf(stderr, "Unable to open file!\n");
            input.lines = NULL;
            return input;
        }

        if (read_from_file(&input,fp))
        {
            fprintf(stderr, "Unable to allocate enough memory!\n");
            fclose(fp);
            input.lines_allocated *= -1;
            return input;
        }
        fclose(fp);
    }
    else
    {
        if (read_from_stdin(&input))
        {
            fprintf(stderr, "Unable to allocate enough memory!\n");
            input.lines_allocated *= -1;
            return input;
        }
    }

    if (input.error_occurred)
        fprintf(stderr, "Unable to read whole line!\n");

    return input;
}

void free_all(input_t *input)
{
    if (input->lines_allocated < 0)
    {
        for (long i = 0; i < input->lines_allocated * (-1); i++)
        {
            free(input->lines[i]);
        }
        free(input->lines);
    }
    else
    {
        for (long i = 0; i < input->line_number; i++)
        {
            free(input->lines[i]);
        }
        free(input->lines);
    }
}
