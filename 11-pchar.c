#include "main.h"

/**
 * monty_pchar - opcode to print the char at the top of the stack
 * @stack: A pointer to the top of a stack
 * @line_number: current working position
 */

void monty_pchar(stack_t **stack, unsigned int line_number)
{
	stack_t *top_node = *stack;
	int ascii_value;

	if (!top_node)
	{
		handle_error(line_number, "can't pchar, stack empty");
	}

	ascii_value = top_node->n;

	if (ascii_value < 0 || ascii_value > 127)
	{
		handle_error(line_number, "can't pchar, calue out of range");
	}

	printf("%c\n", (char)ascii_value);
}
