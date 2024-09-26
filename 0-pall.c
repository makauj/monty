#include "main.h"

/**
 * monty_pall - prints the values of a stack
 * @stack: pointer to the top of a stack
 * @line_number: position of current operation
 *
 * Return: void
 */

void monty_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *head = *stack;

	(void)(line_number);

	while (head)
	{
		printf("%d\n", head->n);
		head = head->next;
	}
}
