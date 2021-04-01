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

typedef struct input {
    char **lines;
    size_t line_number;
    size_t lines_allocated;
}input_t;

void usage()
{
    printf(
           "Usage:\n"
           " tail YOUR-FILE\n"
           " tail -n (+/-)NUMBER-OF-LINES-TO-PRINT YOUR-FILE\n"
           " tail -n (+/-)NUMBER-OF-LINES-TO-PRINT < YOUR-FILE\n");
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

// REDO
int read_from_stdin(input_t *input)
{
    int end_char = 0;
    while (end_char != EOF)
    {
        if ((input->lines[input->line_number] = calloc(MAX_LINES + 1, sizeof(char))) == NULL)
        {
            fprintf(stderr, "Unable to allocate enough memory!\n");
            input->line_number *= -1;
            return -1;
        }

        scanf("%s",input->lines[input->line_number]);
        input->line_number++;
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
    input.line_number = 0;
    input.lines_allocated = 0;

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
            input.line_number *= -1;
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
            input.line_number *= -1;
            return input;
        }
    }
    return input;
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
            if (input.lines_allocated < 0)
            {
                for (size_t i = 0; i < input.lines_allocated*(-1); i++)
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
            input = get_input(argv[3],true);

            // input.line_number - lines_to_print
            for (size_t i = input.line_number - lines_to_print-1; i < input.line_number; i++)
            {
                printf("%s\n", input.lines[i]);
            }

            if (input.line_number < 0)
            {
                for (size_t i = 0; i < input.lines_allocated * (-1); i++)
                {
                    free(input.lines[i]);
                }
            }
            else
            {
                for (size_t i = 0; i < input.lines_allocated; i++)
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
