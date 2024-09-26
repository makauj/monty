#include "main.h"

/**
 * monty_push - function to add a value to a list
 * @stack: A pointer to the top of a stack
 * @line_value: current working position
 */

void monty_push(stack_t **stack, unsigned int line_value)
{
	long val;
	stack_t *new_node = malloc(sizeof(stack_t));
	char *endptr;

	if (*endptr != '\0')
	{
		handle_error(line_value, "usage: push integer");
	}

	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	val = strtol(token, &endptr, 10);
	new_node->n = (int)val;
	new_node->next = *stack;
	new_node->prev = NULL;
	if (*stack)
	{
		(*stack)->prev = new_node;
	}
	*stack = new_node;
}

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
