#include "main.h"

/**
 * monty-sub - opcaoe to subtract the first 2 elements in a stack
 * @stack: A pointer to the top of a stack
 * @line_value: current working position
 */

void monty_sub(stack_t **stack, unsigned int line_number)
{
	stack_t *top_node = *stack;
	stack_t *next_node;

	if (!top_node || !top_node->next)
		handle_error(line_number, "can't sub, stack too short");

	next_node = top_node->next;
	next_node->n -= top_node->n;

	*stack = next_node;
	next_node->next = top_node->next;

	if (top_node->next)
	{
		top_node->next->prev = next_node;
	}

	free(top_node);
}
