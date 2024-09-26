#include "main.h"

/**
 * monty_pstr - Opcode to print the string contained in a stack
 * @stack: A pointer to the top node in a stack
 * @line_number: The current working line number
 */

void monty_pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;
	char character;
	int av;

	if (!current)
		return;
	while (current)
	{
		av = current->n;
		if (av == 0 || av < 0 || av > 127)
			break;

		character = (char)av;
		printf("%c", character);

		current = current->next;
	}
	printf("\n");
}
