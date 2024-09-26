#include "main.h"
/**
 * pstr - Prints the string starting at the top of the stack.
 * @stack: Double pointer to the stack.
 * @line_number: The current line number in the file.
 */
void monty_pstr(stack_t **stack, unsigned int line_number)
{
    stack_t *current = *stack;
    int value;

    if (current == NULL)
    {
        printf("\n");
        return;
    }

    while (current != NULL)
    {
        value = current->n;

        if (value == 0 || value < 0 || value > 127)
            break;

        printf("%c", (char)value);

        current = current->next;
    }

    printf("\n");
}