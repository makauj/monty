#include "main.h"

/**
 * monty_add - function adds the top 2 elements in a stack
 * @stack: pointer to the tp of a stack
 * @line_number: position of current operation
 */
void monty_add(stack_t **stack, unsigned int line_number)
{
	stack_t *top_node = *stack;
	stack_t *next_node;

	if (!top_node || !top_node->next)
	{
		handle_error(line_number, "can't add, stack too short");
	}

	next_node = top_node->next;
	next_node->n += top_node->n;

	*stack = next_node;
	next_node->next = top_node->next;

	if (top_node->next)
	{
		top_node->next->prev = next_node;
	}

	free(top_node);
}
