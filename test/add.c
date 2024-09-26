#include "main.h"

/**
 * add - Adds the top two elements of the stack.
 * @stack: Double pointer to the stack.
 * @line_number: The current line number in the file.
 */
void monty_add(stack_t **stack, unsigned int line_number)
{
    stack_t *first = *stack;
    stack_t *second;
    int sum;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    first = *stack;
    second = (*stack)->next;
    sum = first->n + second->n;

    second->n = sum;
    *stack = second;

    second->prev = NULL;
    second->next = first->next;

    if (first->next)
        first->next->prev = second;

    free(first);
}
