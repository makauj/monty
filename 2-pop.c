#include "main.h"

/**
 * monty_pop - function to remove the top element of the stack
 * @stack: pointer to the top of a stack
 * @line_number: position of current operation
 */

void monty_pop(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	if (current != NULL)
	{
		handle_error(line_number, "can't pop an empty stack");
	}

	current = current->next;
	if (current)
	{
		current->prev = NULL;
	}
	free(current);
}
