#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

typedef struct {
    int *stack;
    size_t stack_size;
    size_t stack_capacity;
} MontyInterpreter;

void initializeInterpreter(MontyInterpreter *interpreter) {
    interpreter->stack = NULL;
    interpreter->stack_size = 0;
    interpreter->stack_capacity = 0;
}

void push(MontyInterpreter *interpreter, int value) {
    /* Unused variable 'i' removed */
    if (interpreter->stack_size >= interpreter->stack_capacity) {
        interpreter->stack_capacity = (interpreter->stack_capacity == 0) ? 1 : interpreter->stack_capacity * 2;
        interpreter->stack = realloc(interpreter->stack, interpreter->stack_capacity * sizeof(int));
        if (!interpreter->stack) {
            fprintf(stderr, "Error: malloc failed\n");
            exit(EXIT_FAILURE);
        }
    }

    interpreter->stack[interpreter->stack_size++] = value;
}

void pall(MontyInterpreter *interpreter) {
    size_t i;  /* Declare i before the loop */

    for (i = 0; i < interpreter->stack_size; ++i) {
        printf("%d\n", interpreter->stack[i]);
    }
}

void processLine(MontyInterpreter *interpreter, const char *line, size_t line_number) {
    char *token = strtok((char *)line, " \t\n");  /* Tokenize the line */

    if (!token) {
        return;  /* Ignore empty lines */
    }

    if (strcmp(token, "push") == 0) {
        token = strtok(NULL, " \t\n");
        if (token) {
            int value = atoi(token);
            push(interpreter, value);
        } else {
            fprintf(stderr, "Error at line %lu: missing argument for push\n", (unsigned long)line_number);
            exit(EXIT_FAILURE);
        }
    } else if (strcmp(token, "pall") == 0) {
        pall(interpreter);
    } else {
        fprintf(stderr, "Error at line %lu: unknown instruction %s\n", (unsigned long)line_number, token);
        exit(EXIT_FAILURE);
    }
}

void executeFile(MontyInterpreter *interpreter, const char *filename) {
    size_t line_number = 0;  /* Declare line_number as size_t */
    char buffer[MAX_LINE_LENGTH];  /* Declare buffer at the beginning */

    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Can't open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        line_number++;
        processLine(interpreter, buffer, line_number);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    MontyInterpreter interpreter;  /* Declare interpreter at the beginning */
    const char *filename;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename> (Monty bytecode file)\n", argv[0]);
        return EXIT_FAILURE;
    }

    filename = argv[1];

    initializeInterpreter(&interpreter);

    executeFile(&interpreter, filename);

    free(interpreter.stack);
    interpreter.stack = NULL;  /* Set to NULL after freeing memory */

    return EXIT_SUCCESS;
}

