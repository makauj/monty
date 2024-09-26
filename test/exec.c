#include "main.h"

/**
 * execute_file - execute file
 * @file: file
 * 
 */
void execute_file(FILE *file)
{
    char *line = malloc(256), *trimmed_line;
    size_t len = 256;
    unsigned int line_number = 0;
    stack_t *stack = NULL;
    char *opcode, *argument;
    instruction_t instruction;
    int value;
    if (!line)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(len), file) != NULL)
    {
        line_number++;

        trimmed_line = line;
        while (*trimmed_line == ' ')
            trimmed_line++;

        if (*trimmed_line == '#' || *trimmed_line == '\0')
        {
            continue;
        }

        opcode = strtok(trimmed_line, " \n");
        argument = strtok(NULL, " \n");

        if (opcode)
        {
            instruction = get_instruction(opcode);
            if (instruction.f)
            {
                if (strcmp(opcode, "push") == 0)
                {
                    if (argument == NULL)
                    {
                        fprintf(stderr, "L%d: usage: push integer\n", line_number);
                        exit(EXIT_FAILURE);
                    }
                    value = atoi(argument);
                    monty_push(&stack, line_number);
                }
                else
                {
                    instruction.f(&stack, line_number);
                }
            }
            else
            {
                fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
                exit(EXIT_FAILURE);
            }
        }
    }

    free(line);
    free_stack(stack); // Clean up stack
}
/**
 * get_instruction - Retrieves the instruction corresponding to an opcode.
 * @opcode: The opcode to look up.
 * 
 * Return: The instruction struct corresponding to the opcode.
 *         If the opcode is not found, it returns NULL.
 */
instruction_t get_instruction(char *opcode)
{
    int i;
    instruction_t instructions[] = {
        {"push", monty_push},
        {"pall", monty_pall},
        {"pint", monty_pint},
        {"pop", monty_pop},
        {"swap", monty_swap},
        {"add", monty_add},
        {"nop", monty_nop},
        {"sub", monty_sub},
        {"div", monty_div},
        {"mul", monty_mul},
        {"mod", monty_mod},
        {"pchar", monty_pchar},
        {"pstr", monty_pstr},
        {NULL, NULL}
    };

    for (i = 0; instructions[i].opcode != NULL; i++)
    {
        if (strcmp(instructions[i].opcode, opcode) == 0)
        {
            return instructions[i];
        }
    }

    instruction_t null_instruction = {NULL, NULL};
    return (null_instruction);
}