#include "monty.h"

/**
 * monty_pop - function to remove the top element of the stack
 * @stack: pointer to the top of a stack
 * @line_number: position of current operation
 */

void monty_pop(stack_t **stack, unsigned int line_number)
{
	stack_t *h;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		fclose(bus.file);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}
	h = *stack;
	*stack = h->next;
	free(h);
}
