#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

int is_number(const char *str);

/**
 * push - Pushes an element onto the stack.
 * @stack: Pointer to the head of the stack.
 * @line_number: Line number in the file.
 */
void push(stack_t **stack, unsigned int line_number)
{
    char buffer[1024]; // Adjust the size as needed
    char *arg = NULL;
    int value;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "L%u: Error reading input\n", line_number);
        exit(EXIT_FAILURE);
    }

    arg = strtok(buffer, " \t\n");

    if (arg == NULL || !is_number(arg))
    {
        fprintf(stderr, "L%u: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    value = atoi(arg);

    /* Create a new stack node */
    stack_t *new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->n = value;
    new_node->prev = NULL;
    new_node->next = *stack;

    if (*stack != NULL)
        (*stack)->prev = new_node;

    *stack = new_node;
}

/**
 * pall - Prints all values on the stack.
 * @stack: Pointer to the head of the stack.
 * @line_number: Line number in the file.
 */
void pall(stack_t **stack, unsigned int line_number)
{
    (void)line_number; /* Unused parameter */

    stack_t *current = *stack;

    while (current != NULL)
    {
        printf("%d\n", current->n);
        current = current->next;
    }
}

/**
 * is_number - Checks if a string represents a number.
 * @str: String to check.
 * Return: 1 if it's a number, 0 otherwise.
 */
int is_number(const char *str)
{
    if (str == NULL || *str == '\0')
        return 0;

    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]) && (i == 0 && str[i] != '-'))
            return 0;
    }

    return 1;
}

/* Additional functions and implementation go here */

