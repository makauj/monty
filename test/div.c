#include "main.h"

/**
 * div - Divides the second top element of the stack by the top element.
 * @stack: Double pointer to the stack.
 * @line_number: The current line number in the file.
 */
void monty_div(stack_t **stack, unsigned int line_number)
{
    stack_t *first = *stack;
    stack_t *second;
    int result;

    if (first == NULL || first->next == NULL)
    {
        fprintf(stderr, "L%d: can't div, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    second = first->next;

    if (first->n == 0)
    {
        fprintf(stderr, "L%d: division by zero\n", line_number);
        exit(EXIT_FAILURE);
    }

    result = second->n / first->n;

    second->n = result;
    *stack = second;

    second->prev = NULL;
    second->next = first->next;

    if (first->next)
        first->next->prev = second;

    free(first);
}
