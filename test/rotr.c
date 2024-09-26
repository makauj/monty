#include "main.h"

/**
 * rotr - Rotates the stack to the bottom.
 * @stack: Double pointer to the stack.
 * @line_number: The current line number in the file (not used here).
 */
void monty_rotr(stack_t **stack, unsigned int line_number)
{
    stack_t *current = *stack;

    if (!stack || !*stack || !(*stack)->next)
        return;

    while (current->next)
        current = current->next;

    current->prev->next = NULL;
    current->prev = NULL;
    current->next = *stack;
    (*stack)->prev = current;
    *stack = current;
}