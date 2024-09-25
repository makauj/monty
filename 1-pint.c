#include "main.h"

/**
 * monty_pint - function prints value at the top of a stack
 * @stack: pointer to the tp of a stack
 * @line_number: position of current operation
 */
void monty_pint(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	(void)(line_number);

	if (!current)
	{
		handle_error(0, "can't pint, stack empty\n");
	}
	printf("%d\n", current->n);
}
