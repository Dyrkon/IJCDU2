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
#define MINIMAL_N_OF_LINES 5
#define ABS(x) ((x < 0) ? (x *= -1) : x)

typedef struct input {
    char **lines;
    long line_number;
    long lines_allocated;
}input_t;

void free_all(input_t *input);

input_t get_input(char *filename, bool is_file);

int read_from_stdin(input_t *input);

int read_from_file(input_t *input, FILE *fp);

int alloc_lines(bool do_realloc, input_t *input, size_t n);

void do_tail(char *filename, char *to_print, bool is_file);

void usage();

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        if (argv[1])

        do_tail(argv[1], "|", true);

    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "-n") != 0)
        {
            printf("Wrong parameters given!\n");
            usage();
        }
        else
            do_tail(NULL, argv[2], false);
    }
    else if (argc == 4)
    {
        if (strcmp(argv[1], "-n") != 0)
        {
            printf("Wrong parameters given!\n");
            usage();
        }
        else
            do_tail(argv[3], argv[2], true);
    }
    else
    {
        printf("Too few parameters supplied!\n");
        usage();
        return 0;
    }

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

void do_tail(char *filename, char *to_print, bool is_file)
{
    input_t input;
    char *end;

    long lines_to_print = 0;

    if (to_print[0] == '|')
        lines_to_print = 10;
    else
        lines_to_print = strtol(to_print,&end, 10);

    input = get_input(!is_file ? "" : filename,is_file);

    if (input.line_number > 0 && input.lines != NULL)
    {
        if (lines_to_print > input.line_number)
            lines_to_print = input.line_number;
    }
    else
    {
        free_all(&input);
        return;
    }

    for (long i = input.line_number - lines_to_print; i < input.line_number; i++)
        printf("%s\n", input.lines[i]);

    free_all(&input);
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
        if ((input->lines = malloc(n * sizeof(char *))) == NULL)
        {
            fprintf(stderr, "Unable to allocate enough memory!\n");
            return 1;
        }
        else
            input->lines_allocated = MINIMAL_N_OF_LINES;
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
            int end_char = 0;
            if ((input->lines[input->line_number] = malloc(MAX_LINES+1 * sizeof(char))) == NULL) {
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
                fprintf(stderr, "Unable to read the full line.\n");
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
            int end_char = 0;
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
                fprintf(stderr, "Unable to read the full line.\n");
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
        return input;
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
        for (long i = 0; i < input->lines_allocated; i++)
        {
            free(input->lines[i]);
        }
        free(input->lines);
    }
}