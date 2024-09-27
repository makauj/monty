#include "monty.h"

/**
* free_stack - frees a doubly linked list
* @stack: head of the stack
*/
void free_stack(stack_t *stack)
{
	stack_t *aux;

	aux = stack;
	while (stack)
	{
		aux = stack->next;
		free(stack);
		stack = aux;
	}
}

/**
* execute - executes the opcode
* @stack: head linked list - stack
* @counter: line_counter
* @file: poiner to monty file
* @content: line content
* Return: no return
*/
int execute(char *content, stack_t **stack, unsigned int counter, FILE *file)
{
	instruction_t opst[] = {
		{"push", monty_push}, {"pall", monty_pall},
		{"pint", monty_pint},
		{"pop", monty_pop}, {"swap", monty_swap},
		{"add", monty_add},
		{"nop", monty_nop}, {"sub", monty_sub},
		{"div", monty_div},
		{"mul", monty_mul}, {"mod", monty_mod},
		{"pchar", monty_pchar},
		{"pstr", monty_pstr},
		{"rotl", monty_rotl},
		{"rotr", monty_rotr},
		{"queue", monty_queue},
		{"stack", monty_stack},
		{NULL, NULL}
				};
	unsigned int i = 0;
	char *op;

	op = strtok(content, " \n\t");
	if (op && op[0] == '#')
		return (0);
	bus.arg = strtok(NULL, " \n\t");
	while (opst[i].opcode && op)
	{
		if (strcmp(op, opst[i].opcode) == 0)
		{	opst[i].f(stack, counter);
			return (0);
		}
		i++;
	}
	if (op && opst[i].opcode == NULL)
	{ fprintf(stderr, "L%d: unknown instruction %s\n", counter, op);
		fclose(file);
		free_stack(*stack);
		exit(EXIT_FAILURE); }
	return (1);
}
