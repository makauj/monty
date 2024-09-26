#include "main.h"

/**
 * free_stack - Frees all elements of the stack.
 * @stack: Pointer to the top of the stack.
 */

void free_stack(stack_t *stack)
{
    stack_t *current = stack;
    stack_t *next_node;

    while (current)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

/**
 * execute_opcode - Executes the given opcode on the stack.
 * @instruction: Pointer to the instruction structure containing opcode and function.
 * @stack: Double pointer to the stack.
 * @line_number: The current line number in the file.
 */
void execute_opcode(instruction_t *instruction, stack_t **stack, unsigned int line_number)
{
    if (instruction == NULL || instruction->f == NULL)
    {
        handle_error("Unknown instruction");
    }

    instruction->f(stack, line_number);
}

/**
 * handle_error - Prints an error message and exits the program.
 * @message: The error message to print.
 */
void handle_error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}
