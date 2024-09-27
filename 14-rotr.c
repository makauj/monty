#include "monty.h"

/**
 * monty_rotr - Opcode that rorates the stack to the bottom
 * @stack: A pointer to the top of a stack
 * @line_number: current working position
 */

void monty_rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *copy;

	(void)line_number;

	copy = *stack;
	if (*stack == NULL || (*stack)->next == NULL)
	{
		return;
	}
	while (copy->next)
	{
		copy = copy->next;
	}
	copy->next = *stack;
	copy->prev->next = NULL;
	copy->prev = NULL;
	(*stack)->prev = copy;
	(*stack) = copy;
}
