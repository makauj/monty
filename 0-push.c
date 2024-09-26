#include "main.h"

/**
 * monty_push - function to add a value to a list
 * @stack: A pointer to the top of a stack
 * @line_value: current working position
 */

void monty_push(stack_t **stack, unsigned int line_value)
{
	int n;
	stack_t *new_node = malloc(sizeof(stack_t));
	char *value = NULL;

	if (!value || !isdigit(value[0]))
	{
		handle_error(line_value, "usage: push integer");
	}
	n = atoi(value);

	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = n;
	new_node->next = *stack;
	new_node->prev = NULL;
	if (*stack)
	{
		(*stack)->prev = new_node;
	}
	*stack = new_node;
}
