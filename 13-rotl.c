#include "main.h"

/**
 * monty_rotl - function prints value at the top of a stack
 * @stack: pointer to the tp of a stack
 * @line_number: position of current operation
 */

void monty_rotl(stack_t **stack, unsigned int list_number)
{
	stack_t *top_node = *stack;
	stack_t *second_node, *last_node;

	(void)list_number;

	if (!top_node || !top_node->next)
		return;

	second_node = top_node->next;
	top_node->next = NULL;
	second_node->prev = NULL;

	last_node = second_node;

	while (last_node->next)
	{
		last_node = last_node->next;
	}

	last_node->next = top_node;
	top_node->prev = last_node;

	*stack = second_node;
}
