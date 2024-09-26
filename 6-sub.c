#include "main.h"

/**
 * monty-sub - opcaoe to subtract the first 2 elements in a stack
 * @stack: A pointer to the top of a stack
 * @line_value: current working position
 */

void monty_sub(stack_t **stack, unsigned int line_number)
{
	stack_t *aux;
	int sus, nodes;

	aux = *stack;
	for (nodes = 0; aux != NULL; nodes++)
		aux = aux->next;
	if (nodes < 2)
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
		fclose(bus.file);
		free(bus.content);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}
	aux = *stack;
	sus = aux->next->n - aux->n;
	aux->next->n = sus;
	*stack = aux->next;
	free(aux);
}
