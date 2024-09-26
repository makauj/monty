#include "main.h"

/**
 * mul - Multiplies the second top element of the stack with the top element.
 * @stack: Double pointer to the stack.
 * @line_number: The current line number in the file.
 */
void monty_mul(stack_t **stack, unsigned int line_number)
{
    stack_t *first = *stack;
    stack_t *second;
    int result;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    first = *stack;
    second = (*stack)->next;
    result = second->n * first->n;

    second->n = result;
    *stack = second;

    second->prev = NULL;
    second->next = first->next;

    if (first->next)
        first->next->prev = second;

    free(first);
}
