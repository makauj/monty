#include "main.h"

/**
 * monty_rotr - Opcode that rorates the stack to the bottom
 * @stack: A pointer to the top of a stack
 * @line_number: current working position
 */

void monty_rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *top_node = *stack;
	stack_t *last_node;

	(void)line_number;

	if (!top_node || !top_node->next)
		return;

	while (last_node->next)
	{
		last_node = last_node->next;
	}

	last_node->prev->next = NULL;
	last_node->prev = NULL;
	last_node->next = top_node;
	top_node->prev = last_node;

	*stack = last_node;
}
