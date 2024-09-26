#include "main.h"

/**
 * main - Entry point for the Monty bytecode interpreter
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(int argc, char *argv[])
{
    stack_t *stack = NULL;
    char *command = NULL;
    size_t len = 0;
    unsigned int line_number = 1;
    char *token, *endptr;
    long value;

    if (argc != 1)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    while (getline(&command, &len, stdin) != -1)
    {
        token = strtok(command, DELIMS);
        if (token == NULL)
        {
            line_number++;
            continue;
        }

        if (strcmp(token, "push") == 0)
        {
            token = strtok(NULL, DELIMS);
            if (token == NULL)
                handle_error(line_number, "usage: push integer");

            value = strtol(token, &endptr, 10);
            if (*endptr != '\0')
                handle_error(line_number, "usage: push integer");

            monty_push(&stack, line_number);
        }
        else if (strcmp(token, "pall") == 0)
        {
            monty_pall(&stack, line_number);
        }
        else if (strcmp(token, "pint") == 0)
        {
            monty_pint(&stack, line_number);
        }
        else if (strcmp(token, "pop") == 0)
        {
            monty_pop(&stack, line_number);
        }
        else if (strcmp(token, "swap") == 0)
        {
            monty_swap(&stack, line_number);
        }
        else if (strcmp(token, "add") == 0)
        {
            monty_add(&stack, line_number);
        }
        else if (strcmp(token, "nop") == 0)
        {
            monty_nop(&stack, line_number);
        }
        else if (strcmp(token, "sub") == 0)
        {
            monty_sub(&stack, line_number);
        }
        else if (strcmp(token, "div") == 0)
        {
            monty_div(&stack, line_number);
        }
        else if (strcmp(token, "mul") == 0)
        {
            monty_mul(&stack, line_number);
        }
        else if (strcmp(token, "mod") == 0)
        {
            monty_mod(&stack, line_number);
        }
        else if (strcmp(token, "pchar") == 0)
        {
            monty_pchar(&stack, line_number);
        }
        else if (strcmp(token, "pstr") == 0)
        {
            monty_pstr(&stack, line_number);
        }
        else if (strcmp(token, "rotl") == 0)
        {
            monty_rotl(&stack, line_number);
        }
        else if (strcmp(token, "rotr") == 0)
        {
            monty_rotr(&stack, line_number);
        }
        else
        {
            handle_error(line_number, "unknown instruction");
        }

        line_number++;
    }

    free(command);
    free_stack(stack);
    return (EXIT_SUCCESS);
}
