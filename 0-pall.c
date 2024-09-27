#include "monty.h"

/**
 * monty_pall - prints the values of a stack
 * @stack: pointer to the top of a stack
 * @line_number: position of current operation
 *
 * Return: void
 */

void monty_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *head;

	(void)(line_number);

	head = *stack;
	while (head != NULL)
	{
		printf("%d\n", head->n);
		head = head->next;
		if (head == *stack)
		{
			return;
		}
	}
}
