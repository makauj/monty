#include "main.h"

/**
 * monty_mul - opcode to multiply the top 2 elements of a stack
 * @stack: A pointer to the top of a stack
 * @line_number: current working position
 */

void monty_mul(stack_t **stack, unsigned int line_number)
{
	stack_t *h;
	int len = 0, aux;

	h = *stack;
	while (h)
	{
		h = h->next;
		len++;
	}
	if (len < 2)
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
		fclose(bus.file);
		free(bus.content);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}
	h = *stack;
	aux = h->next->n * h->n;
	h->next->n = aux;
	*stack = h->next;
	free(h);
}
