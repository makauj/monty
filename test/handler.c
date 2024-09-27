#include "monty.h"
#include <string.h>

/**
 * monty_execute_instruction - Executes a given opcode
 * @instructions: Array of opcode structures
 * @opcode: The opcode to execute
 * @stack: Pointer to the top of the stack
 * @line_number: Current line number in the bytecode file
 */
void monty_execute_instruction(instruction_t *instructions, char *opcode, stack_t **stack, unsigned int line_number) {
    int i;

    for (i = 0; instructions[i].opcode; i++) {
        if (strcmp(opcode, instructions[i].opcode) == 0) {
            instructions[i].f(stack, line_number);
            return;
        }
    }
    monty_handle_error("unknown instruction", NULL, line_number);
}
#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * monty_handle_error - Handles errors and prints appropriate messages
 * @message: The error message
 * @file: The file name (if applicable)
 * @line_number: The line number (if applicable)
 */
void monty_handle_error(const char *message, const char *file, unsigned int line_number) {
    if (file) {
        fprintf(stderr, "%s %s\n", message, file);
    } else {
        fprintf(stderr, "L%u: %s\n", line_number, message);
    }
    exit(EXIT_FAILURE);
}
#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * monty_parse_file - Parses the given bytecode file
 * @filename: The name of the file to parse
 */
void monty_parse_file(const char *filename) {
    FILE *file;
    char *line;
    size_t len;
    stack_t *stack;
    unsigned int line_number;

    file = fopen(filename, "r");
    line = NULL;
    len = 0;
    stack = NULL;
    line_number = 0;

    if (!file) {
        monty_handle_error("Error: Can't open file", filename, 0);
    }

    while (getline(&line, &len, file) != -1) {
        line_number++;
        char *opcode = strtok(line, " \n");
        if (opcode) {
            monty_execute_instruction(instructions, opcode, &stack, line_number);
        }
    }

    free(line);
    fclose(file);
    monty_free_stack(&stack);
}
#include "monty.h"
#include <stdlib.h>

/**
 * monty_free_stack - Frees the stack
 * @stack: Pointer to the top of the stack
 */
void monty_free_stack(stack_t **stack) {
    stack_t *current;
    stack_t *next_node;

    current = *stack;
    while (current) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    *stack = NULL;
}

