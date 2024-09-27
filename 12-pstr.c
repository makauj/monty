#include "monty.h"

/**
 * monty_pstr - Opcode to print the string contained in a stack
 * @stack: A pointer to the top node in a stack
 * @line_number: The current working line number
 */

void monty_pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *h;

	(void)line_number;

	h = *stack;
	while (h)
	{
		if (h->n > 127 || h->n <= 0)
		{
			break;
		}
		printf("%c", h->n);
		h = h->next;
	}
	printf("\n");
}
