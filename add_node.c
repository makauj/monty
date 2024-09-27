#include "monty.h"

/**
 * add_node - add a new node to a circular linked list
 * @stack: double pointer to the beginning of the circular linked list
 * @n: value to add to the new node
 *
 * Return: 0
 *
 */
stack_t *add_node(stack_t **stack, int n)
{
	stack_t *new_node, *aux;

	aux = *stack;
	new_node = malloc(sizeof(stack_t));

	if (new_node == NULL)
	{
		printf("Error\n");
		exit(0);
	}

	if (aux)
	{
		aux->prev = new_node;
	}

	new_node->n = n;
	new_node->next = *stack;
	new_node->prev = NULL;
	*stack = new_node;

	return (0);
}
