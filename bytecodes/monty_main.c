#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

bus_t bus = {NULL, NULL, NULL, 0};

/**
 * main - function for monty code interpreter
 * @argc: argument count
 * @argv: argument value
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
    char *content = NULL;
    FILE *file;
    size_t size = 0;
    stack_t *stack = NULL;
    unsigned int counter = 0;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }
    file = fopen(argv[1], "r");
    bus.file = file;
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    while (getline(&content, &size, file) != -1)
    {
        bus.content = content;
        counter++;
        execute(clean_line(content), &stack, counter, file);
    }
    free(content);
    free_stack(stack);
    fclose(file);
    return (0);
}
