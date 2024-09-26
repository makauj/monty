#include "main.h"

/**
 * monty_mod - opcode to multiply the top 2 elements of a stack
 * @stack: A pointer to the top of a stack
 * @line_value: current working position
 */

void monty_mod(stack_t **stack, unsigned int line_number)
{
	stack_t *top_node = *stack;
	stack_t *next_node;

	if (!top_node || !top_node->next)
		handle_error(line_number, "can't mod, stack too short");

	if (top_node->n == 0)
	{
		handle_error(line_number, "division by zero");
	}

	next_node = top_node->next;

	next_node->n %=top_node->n;

	*stack = next_node;
	next_node->prev = NULL;
	next_node->next = top_node->next;

	if (top_node->next)
	{
		top_node->next->prev = next_node;
	}

	free(top_node);
}
