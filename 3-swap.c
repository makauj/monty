#include "main.h"

/**
 * monty_swap - function swaps the two top elements of a stack
 * @stack: pointer to the tp of a stack
 * @line_number: position of current operation
 */

void monty_swap(stack_t **stack, unsigned int line_number)
{
	stack_t *top_node = *stack;
	stack_t *temp;
	stack_t *next_node;

	if (!top_node || !top_node->next)
	{
		handle_error(line_number, "can't swap, stack too short");
	}
	next_node = top_node->next;
	top_node->next = next_node->next;
	next_node->prev = NULL;

	if (top_node->next)
	{
		top_node->next->prev = top_node;
	}
	next_node->next = top_node;
	top_node->prev = next_node;

	*stack = next_node;
}
