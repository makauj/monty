#include "main.h"

/**
 * sub - Subtracts the top element of the stack from the second top element.
 * @stack: Double pointer to the stack.
 * @line_number: The current line number in the file.
 */
void monty_sub(stack_t **stack, unsigned int line_number)
{
    stack_t *first = *stack;
    stack_t *second;
    int difference;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    second = (*stack)->next;
    difference = second->n - first->n;

    second->n = difference;
    *stack = second;

    /* Update the links */
    second->prev = NULL;
    second->next = first->next;

    if (first->next)
        first->next->prev = second;

    free(first);
}
