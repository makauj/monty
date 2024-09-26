#include "main.h"

/**
 * mod - Computes the remainder of the division of the second top element
 *       of the stack by the top element.
 * @stack: Double pointer to the stack.
 * @line_number: The current line number in the file.
 */
void monty_mod(stack_t **stack, unsigned int line_number)
{
    stack_t *first = *stack;
    stack_t *second;
    int result;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    first = *stack;
    second = (*stack)->next;

    if (first->n == 0)
    {
        fprintf(stderr, "L%d: division by zero\n", line_number);
        exit(EXIT_FAILURE);
    }

    result = second->n % first->n;

    second->n = result;
    stack = second;

    second->prev = NULL;
    second->next = first->next;

    if (first->next)
        first->next->prev = second;

    free(first);
}
