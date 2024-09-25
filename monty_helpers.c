#include "main.h"

/**
 * free_stack - function to free memory
 * @stack: pointer to the top of a stack
 */
void free_stack(stack_t *stack)
{
	stack_t *current = stack;
	stack_t *temp;

	while (current)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}

/**
 * handle_error - error handling function
 * @line_num: line number being executed
 * @message: message to display
 */
void handle_error(unsigned int line_num, const char *message)
{
	fprintf(stderr, "L%u: %s\n", line_num, message);
	exit(EXIT_FAILURE);
}
