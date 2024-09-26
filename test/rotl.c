#include "main.h"

/**
 * rotl - Rotates the stack to the top.
 * @stack: Double pointer to the stack.
 * @line_number: The current line number in the file (not used here).
 */
void monty_rotl(stack_t **stack, unsigned int line_number)
{
    stack_t *top = *stack;
    stack_t *current;
    if (!stack || !*stack || !(*stack)->next)
        return;

    *stack = top->next;
    (*stack)->prev = NULL;

    current = *stack;
    while (current->next)
        current = current->next;

    current->next = top;
    top->next = NULL;
    top->prev = current;
}
