#include "main.h"

/**
 * swap - Swaps the top two elements of the stack.
 * @stack: Double pointer to the stack.
 * @line_number: The current line number in the file.
 */
void monty_swap(stack_t **stack, unsigned int line_number)
{
    stack_t *first = *stack;
    stack_t * second;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    second = (*stack)->next;

    first->next = second->next;
    second->prev = NULL;
    second->next = first;
    first->prev = second;

    
    *stack = second;

    if (first->next)
        first->next->prev = first;
}
