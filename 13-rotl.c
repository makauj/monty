#include "main.h"

/**
 * monty_rotl - function prints value at the top of a stack
 * @stack: pointer to the tp of a stack
 * @line_number: position of current operation
 */

void monty_rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack, *aux;

	(void)line_number;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		return;
	}
	aux = (*stack)->next;
	aux->prev = NULL;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = *stack;
	(*stack)->next = NULL;
	(*stack)->prev = tmp;
	(*stack) = aux;
}
