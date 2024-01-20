/* monty.h */
#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

typedef struct {
    int *stack;
    unsigned int stack_size;
    unsigned int stack_capacity;
} MontyInterpreter;

void initializeInterpreter(MontyInterpreter *interpreter);
void push(MontyInterpreter *interpreter, int value);
void pall(MontyInterpreter *interpreter);
void processLine(MontyInterpreter *interpreter, const char *line, unsigned int line_number);
void executeFile(MontyInterpreter *interpreter, const char *filename);

#endif /* MONTY_H */

