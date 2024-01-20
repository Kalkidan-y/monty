#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * push - Pushes an element onto the stack.
 * @stack: Pointer to the head of the stack.
 * @line_number: Line number in the file.
 */
void push(stack_t **stack, unsigned int line_number)
{
    char *arg = strtok(NULL, " \t\n");

    if (arg == NULL || !is_number(arg))
    {
        fprintf(stderr, "L%u: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    int value = atoi(arg);

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

