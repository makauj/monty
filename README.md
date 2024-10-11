# 0x19. C - Stacks, Queues - LIFO, FIFO

## Learning Objectives
1. What do LIFO and FIFO mean
2. What is a stack, and when to use it
3. What is a queue, and when to use it
4. What are the common implementations of stacks and queues
5. What are the most common use cases of stacks and queues
6. What is the proper way to use global variables

## Tasks

### Implement the `push` and `pall` opcodes.

**The push opcode**

The opcode push pushes an element to the stack.

	- Usage: `push <int>`
		- where `<int>` is an integer
	- if `<int>` is not an integer or if there is no argument given to `push`, print the error message `L<line_number>: usage: push integer`, followed by a new line, and `exit` with the status `EXIT_FAILURE`
		- where is the line number in the file
	- You won’t have to deal with overflows. Use the atoi function

**The pall opcode**

The opcode `pall` prints all the values on the stack, starting from the top of the stack.

	- Usage `pall`
	- Format: see example
	- If the stack is empty, don’t print anything

### Implement the `pint` opcode.

**The pint opcode**

The opcode `pint` prints the value at the top of the stack, followed by a new line.

	- Usage: `pint`
	- If the stack is empty, print the error message `L<line_number>: can't pint, stack empty`, followed by a new line, and `exit` with the status `EXIT_FAILURE`

### Implement the `pop` opcode.

**The pop opcode**

The opcode pop removes the top element of the stack.

	- Usage: `pop`
	- If the stack is empty, print the error message `L<line_number>: can't pop an empty stack`, followed by a new line, and exit with the status `EXIT_FAILURE`
3. Implement the `swap` opcode.

**The swap opcode**

The opcode swap swaps the top two elements of the stack.

	- Usage: `swap`
	- If the stack contains less than two elements, print the error message `L<line_number>: can't swap, stack too short`, followed by a new line, and `exit` with the status `EXIT_FAILURE`

### Implement the `add` opcode.

**The add opcode**

The opcode `add` adds the top two elements of the stack.

	- Usage: `add`
	- If the stack contains less than two elements, print the error message `L<line_number>: can't add, stack too short`, followed by a new line, and `exit` with the status `EXIT_FAILURE`
	- The result is stored in the second top element of the stack, and the top element is removed, so that at the end:
		- The top element of the stack contains the result
		- The stack is one element shorter
### Implement the `nop` opcode.

**The nop opcode**

The opcode nop doesn’t do anything.

	- Usage: `nop`

# Monty Notes

## Monty Code
This is structured in a way that each code block is in it's own file.
### monty.h (Header File)
Create a header file to define the structures and function prototypes.

```c
#ifndef MONTY_H
#define MONTY_H

typedef struct stack_s {
    int n;
    struct stack_s *prev;
    struct stack_s *next;
} stack_t;

typedef struct instruction_s {
    char *opcode;
    void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

void monty_push(stack_t **stack, unsigned int line_number);
void monty_pall(stack_t **stack, unsigned int line_number);
void monty_free_stack(stack_t **stack);
void monty_execute_instruction(instruction_t *instructions, char *opcode, stack_t **stack, unsigned int line_number);
void monty_handle_error(const char *message, const char *file, unsigned int line_number);
void monty_parse_file(const char *filename);

#endif /* MONTY_H */
```

### monty_push.c
This file will contain the implementation of the `monty_push` function.

```c
#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * monty_push - Opcode to push an integer onto the stack
 * @stack: Pointer to the top of the stack
 * @line_number: Position in code we are working
 */
void monty_push(stack_t **stack, unsigned int line_number) {
    stack_t *new_node;
    char *arg = strtok(NULL, " \n");

    if (!arg || atoi(arg) == 0 && strcmp(arg, "0") != 0) {
        monty_handle_error("usage: push integer", NULL, line_number);
    }

    new_node = malloc(sizeof(stack_t));
    if (!new_node) {
        monty_handle_error("Error: malloc failed", NULL, 0);
    }

    new_node->n = atoi(arg);
    new_node->prev = NULL;
    new_node->next = *stack;

    if (*stack) {
        (*stack)->prev = new_node;
    }

    *stack = new_node;
}
```

### monty_pall.c
This file will contain the implementation of the `monty_pall` function.

```c
#include "monty.h"
#include <stdio.h>

/**
 * monty_pall - Opcode to print all values in the stack
 * @stack: Pointer to the top of the stack
 * @line_number: Position in code we are working
 */
void monty_pall(stack_t **stack, unsigned int line_number) {
    stack_t *current;

    current = *stack;
    while (current) {
        printf("%d\n", current->n);
        current = current->next;
    }
}
```

### monty_execute_instruction.c
This file will contain the implementation of the instruction execution function.

```c
#include "monty.h"
#include <string.h>

/**
 * monty_execute_instruction - Executes a given opcode
 * @instructions: Array of opcode structures
 * @opcode: The opcode to execute
 * @stack: Pointer to the top of the stack
 * @line_number: Current line number in the bytecode file
 */
void monty_execute_instruction(instruction_t *instructions, char *opcode, stack_t **stack, unsigned int line_number) {
    int i;

    for (i = 0; instructions[i].opcode; i++) {
        if (strcmp(opcode, instructions[i].opcode) == 0) {
            instructions[i].f(stack, line_number);
            return;
        }
    }
    monty_handle_error("unknown instruction", NULL, line_number);
}
```

### monty_handle_error.c
This file will contain the error handling function.

```c
#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * monty_handle_error - Handles errors and prints appropriate messages
 * @message: The error message
 * @file: The file name (if applicable)
 * @line_number: The line number (if applicable)
 */
void monty_handle_error(const char *message, const char *file, unsigned int line_number) {
    if (file) {
        fprintf(stderr, "%s %s\n", message, file);
    } else {
        fprintf(stderr, "L%u: %s\n", line_number, message);
    }
    exit(EXIT_FAILURE);
}
```

### monty_parse_file.c
This file will contain the file parsing function.

```c
#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * monty_parse_file - Parses the given bytecode file
 * @filename: The name of the file to parse
 */
void monty_parse_file(const char *filename) {
    FILE *file;
    char *line;
    size_t len;
    stack_t *stack;
    unsigned int line_number;

    file = fopen(filename, "r");
    line = NULL;
    len = 0;
    stack = NULL;
    line_number = 0;

    if (!file) {
        monty_handle_error("Error: Can't open file", filename, 0);
    }

    while (getline(&line, &len, file) != -1) {
        line_number++;
        char *opcode = strtok(line, " \n");
        if (opcode) {
            monty_execute_instruction(instructions, opcode, &stack, line_number);
        }
    }

    free(line);
    fclose(file);
    monty_free_stack(&stack);
}
```

### monty_free_stack.c
This file will handle freeing the stack.

```c
#include "monty.h"
#include <stdlib.h>

/**
 * monty_free_stack - Frees the stack
 * @stack: Pointer to the top of the stack
 */
void monty_free_stack(stack_t **stack) {
    stack_t *current;
    stack_t *next_node;

    current = *stack;
    while (current) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    *stack = NULL;
}
```

### Main File (monty.c)
Finally, here’s how the main file would look.

```c
#include "monty.h"

instruction_t instructions[] = {
    {"push", monty_push},
    {"pall", monty_pall},
    {NULL, NULL}
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        monty_handle_error("USAGE: monty file", NULL, 0);
    }
    monty_parse_file(argv[1]);
    return EXIT_SUCCESS;
}
```

### Compilation
You can compile the files together as follows:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=c89 *.c -o monty
```

### Summary
- Each function is separated into its own file.
- The main functionality remains unchanged.
- Header file `monty.h` contains the necessary declarations.

As we proceed with additional functionality, we can continue to create new `.c` files for each opcode or feature.

Here’s how to implement the `pint` opcode, including the necessary function and updates to the existing structure.

### monty_pint.c
Create a new file for the `pint` opcode implementation.

```c
#include "monty.h"
#include <stdio.h>

/**
 * monty_pint - Opcode to print the value at the top of the stack
 * @stack: Pointer to the top of the stack
 * @line_number: Position in code we are working
 */
void monty_pint(stack_t **stack, unsigned int line_number) {
    if (!stack || !*stack) {
        monty_handle_error("can't pint, stack empty", NULL, line_number);
    }
    printf("%d\n", (*stack)->n);
}
```

### Update monty.h
Add the prototype for the `monty_pint` function to the header file.

```c
void monty_pint(stack_t **stack, unsigned int line_number);
```

### Update instructions Array in monty.c
Modify the instructions array in the main file to include the `pint` opcode.

```c
instruction_t instructions[] = {
    {"push", monty_push},
    {"pall", monty_pall},
    {"pint", monty_pint},
    {NULL, NULL}
};
```

### Summary of Changes
1. **`monty_pint.c`**: Implemented the `monty_pint` function, which prints the top value of the stack or handles the error if the stack is empty.
2. **Updated `monty.h`**: Added the function prototype for `monty_pint`.
3. **Updated `monty.c`**: Added the `pint` opcode to the instructions array.

### Compilation
You can compile the code as before:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=c89 *.c -o monty
```

Now, when you run the Monty interpreter with a bytecode file containing the `pint` opcode, it will print the value at the top of the stack or report an error if the stack is empty.


Here’s how to implement the `pop` opcode, including the necessary function and updates.

### monty_pop.c
Create a new file for the `pop` opcode implementation.

```c
#include "monty.h"
#include <stdio.h>

/**
 * monty_pop - Opcode to remove the top element of the stack
 * @stack: Pointer to the top of the stack
 * @line_number: Position in code we are working
 */
void monty_pop(stack_t **stack, unsigned int line_number) {
    stack_t *top_node;

    if (!stack || !*stack) {
        monty_handle_error("can't pop an empty stack", NULL, line_number);
    }

    top_node = *stack;
    *stack = (*stack)->next;
    if (*stack) {
        (*stack)->prev = NULL;
    }
    free(top_node);
}
```

### Update monty.h
Add the prototype for the `monty_pop` function to the header file.

```c
void monty_pop(stack_t **stack, unsigned int line_number);
```

### Update instructions Array in monty.c
Modify the instructions array in the main file to include the `pop` opcode.

```c
instruction_t instructions[] = {
    {"push", monty_push},
    {"pall", monty_pall},
    {"pint", monty_pint},
    {"pop", monty_pop},
    {NULL, NULL}
};
```

### Summary of Changes
1. **`monty_pop.c`**: Implemented the `monty_pop` function, which removes the top element of the stack or handles the error if the stack is empty.
2. **Updated `monty.h`**: Added the function prototype for `monty_pop`.
3. **Updated `monty.c`**: Added the `pop` opcode to the instructions array.

### Compilation
You can compile the code as before:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=c89 *.c -o monty
```

With this implementation, the Monty interpreter can now handle the `pop` opcode. When invoked, it will remove the top element of the stack or display an error if the stack is empty.


Here’s how to implement the `swap` opcode, along with the necessary function and updates to the relevant files.

### monty_swap.c
Create a new file for the `swap` opcode implementation.

```c
#include "monty.h"
#include <stdio.h>

/**
 * monty_swap - Opcode to swap the top two elements of the stack
 * @stack: Pointer to the top of the stack
 * @line_number: Position in code we are working
 */
void monty_swap(stack_t **stack, unsigned int line_number) {
    stack_t *first, *second;

    if (!stack || !*stack || !(*stack)->next) {
        monty_handle_error("can't swap, stack too short", NULL, line_number);
    }

    first = *stack;
    second = first->next;

    first->next = second->next;
    first->prev = second;
    second->prev = NULL;

    if (second->next) {
        second->next->prev = first;
    }

    second->next = first;
    *stack = second;
}
```

### Update monty.h
Add the prototype for the `monty_swap` function to the header file.

```c
void monty_swap(stack_t **stack, unsigned int line_number);
```

### Update instructions Array in monty.c
Modify the instructions array in the main file to include the `swap` opcode.

```c
instruction_t instructions[] = {
    {"push", monty_push},
    {"pall", monty_pall},
    {"pint", monty_pint},
    {"pop", monty_pop},
    {"swap", monty_swap},
    {NULL, NULL}
};
```

### Summary of Changes
1. **`monty_swap.c`**: Implemented the `monty_swap` function, which swaps the top two elements of the stack or handles the error if there aren’t enough elements.
2. **Updated `monty.h`**: Added the function prototype for `monty_swap`.
3. **Updated `monty.c`**: Added the `swap` opcode to the instructions array.

### Compilation
You can compile the code as before:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=c89 *.c -o monty
```

Now the Monty interpreter can handle the `swap` opcode. When invoked, it will swap the top two elements of the stack or display an error if there aren’t enough elements.


Here’s how to implement the `add` opcode, along with the necessary function and updates to the relevant files.

### monty_add.c
Create a new file for the `add` opcode implementation.

```c
#include "monty.h"
#include <stdio.h>

/**
 * monty_add - Opcode to add the top two elements of the stack
 * @stack: Pointer to the top of the stack
 * @line_number: Position in code we are working
 */
void monty_add(stack_t **stack, unsigned int line_number) {
    stack_t *first, *second;
    int sum;

    if (!stack || !*stack || !(*stack)->next) {
        monty_handle_error("can't add, stack too short", NULL, line_number);
    }

    first = *stack;
    second = first->next;

    sum = first->n + second->n;
    second->n = sum;

    *stack = second;
    second->prev = NULL;
    free(first);
}
```

### Update monty.h
Add the prototype for the `monty_add` function to the header file.

```c
void monty_add(stack_t **stack, unsigned int line_number);
```

### Update instructions Array in monty.c
Modify the instructions array in the main file to include the `add` opcode.

```c
instruction_t instructions[] = {
    {"push", monty_push},
    {"pall", monty_pall},
    {"pint", monty_pint},
    {"pop", monty_pop},
    {"swap", monty_swap},
    {"add", monty_add},
    {NULL, NULL}
};
```

### Summary of Changes
1. **`monty_add.c`**: Implemented the `monty_add` function, which adds the top two elements of the stack, replaces the second top element with the result, and removes the top element, or handles the error if there aren’t enough elements.
2. **Updated `monty.h`**: Added the function prototype for `monty_add`.
3. **Updated `monty.c`**: Added the `add` opcode to the instructions array.

### Compilation
You can compile the code as before:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=c89 *.c -o monty
```

Now the Monty interpreter can handle the `add` opcode. When invoked, it will add the top two elements of the stack and store the result in the second top element, while removing the top element. If there aren’t enough elements to perform the addition, it will display an error.


Implementing the `nop` opcode is straightforward since it performs no action. Here’s how to create it along with the necessary updates to the relevant files.

### monty_nop.c
Create a new file for the `nop` opcode implementation.

```c
#include "monty.h"

/**
 * monty_nop - Opcode that does nothing
 * @stack: Pointer to the top of the stack
 * @line_number: Position in code we are working
 */
void monty_nop(stack_t **stack, unsigned int line_number) {
    (void)stack;      // Prevent unused parameter warning
    (void)line_number; // Prevent unused parameter warning
}
```

### Update monty.h
Add the prototype for the `monty_nop` function to the header file.

```c
void monty_nop(stack_t **stack, unsigned int line_number);
```

### Update instructions Array in monty.c
Modify the instructions array in the main file to include the `nop` opcode.

```c
instruction_t instructions[] = {
    {"push", monty_push},
    {"pall", monty_pall},
    {"pint", monty_pint},
    {"pop", monty_pop},
    {"swap", monty_swap},
    {"add", monty_add},
    {"nop", monty_nop},
    {NULL, NULL}
};
```

### Summary of Changes
1. **`monty_nop.c`**: Implemented the `monty_nop` function, which simply does nothing.
2. **Updated `monty.h`**: Added the function prototype for `monty_nop`.
3. **Updated `monty.c`**: Added the `nop` opcode to the instructions array.

### Compilation
You can compile the code as before:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=c89 *.c -o monty
```

Now the Monty interpreter can handle the `nop` opcode, which effectively performs no action.


Here’s how to implement the `sub` opcode, along with the necessary function and updates to the relevant files.

### monty_sub.c
Create a new file for the `sub` opcode implementation.

```c
#include "monty.h"
#include <stdio.h>

/**
 * monty_sub - Opcode to subtract the top element from the second top element of the stack
 * @stack: Pointer to the top of the stack
 * @line_number: Position in code we are working
 */
void monty_sub(stack_t **stack, unsigned int line_number) {
    stack_t *first, *second;
    int result;

    if (!stack || !*stack || !(*stack)->next) {
        monty_handle_error("can't sub, stack too short", NULL, line_number);
    }

    first = *stack;
    second = first->next;

    result = second->n - first->n;  // Subtract top from second top
    second->n = result;

    *stack = second;
    second->prev = NULL;
    free(first);
}
```

### Update monty.h
Add the prototype for the `monty_sub` function to the header file.

```c
void monty_sub(stack_t **stack, unsigned int line_number);
```

### Update instructions Array in monty.c
Modify the instructions array in the main file to include the `sub` opcode.

```c
instruction_t instructions[] = {
    {"push", monty_push},
    {"pall", monty_pall},
    {"pint", monty_pint},
    {"pop", monty_pop},
    {"swap", monty_swap},
    {"add", monty_add},
    {"sub", monty_sub},
    {"nop", monty_nop},
    {NULL, NULL}
};
```

### Summary of Changes
1. **`monty_sub.c`**: Implemented the `monty_sub` function, which subtracts the top element from the second top element of the stack, updates the second top element with the result, and removes the top element, or handles the error if there aren’t enough elements.
2. **Updated `monty.h`**: Added the function prototype for `monty_sub`.
3. **Updated `monty.c`**: Added the `sub` opcode to the instructions array.

### Compilation
You can compile the code as before:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=c89 *.c -o monty
```

Now the Monty interpreter can handle the `sub` opcode. When invoked, it will subtract the top element from the second top element of the stack and store the result in the second top element, while removing the top element. If there aren’t enough elements, it will display an error.


Here’s how to implement the `div`, `mul`, and `mod` opcodes, along with the necessary functions and updates to the relevant files.

### monty_div.c
Create a new file for the `div` opcode implementation.

```c
#include "monty.h"
#include <stdio.h>

/**
 * monty_div - Opcode to divide the second top element of the stack by the top element
 * @stack: Pointer to the top of the stack
 * @line_number: Position in code we are working
 */
void monty_div(stack_t **stack, unsigned int line_number) {
    stack_t *first, *second;
    int result;

    if (!stack || !*stack || !(*stack)->next) {
        monty_handle_error("can't div, stack too short", NULL, line_number);
    }

    first = *stack;
    second = first->next;

    if (first->n == 0) {
        monty_handle_error("division by zero", NULL, line_number);
    }

    result = second->n / first->n; // Divide second top by top
    second->n = result;

    *stack = second;
    second->prev = NULL;
    free(first);
}
```

### monty_mul.c
Create a new file for the `mul` opcode implementation.

```c
#include "monty.h"
#include <stdio.h>

/**
 * monty_mul - Opcode to multiply the second top element of the stack with the top element
 * @stack: Pointer to the top of the stack
 * @line_number: Position in code we are working
 */
void monty_mul(stack_t **stack, unsigned int line_number) {
    stack_t *first, *second;
    int result;

    if (!stack || !*stack || !(*stack)->next) {
        monty_handle_error("can't mul, stack too short", NULL, line_number);
    }

    first = *stack;
    second = first->next;

    result = second->n * first->n; // Multiply second top with top
    second->n = result;

    *stack = second;
    second->prev = NULL;
    free(first);
}
```

### monty_mod.c
Create a new file for the `mod` opcode implementation.

```c
#include "monty.h"
#include <stdio.h>

/**
 * monty_mod - Opcode to compute the remainder of the division of the second top element by the top element
 * @stack: Pointer to the top of the stack
 * @line_number: Position in code we are working
 */
void monty_mod(stack_t **stack, unsigned int line_number) {
    stack_t *first, *second;
    int result;

    if (!stack || !*stack || !(*stack)->next) {
        monty_handle_error("can't mod, stack too short", NULL, line_number);
    }

    first = *stack;
    second = first->next;

    if (first->n == 0) {
        monty_handle_error("division by zero", NULL, line_number);
    }

    result = second->n % first->n; // Modulus of second top by top
    second->n = result;

    *stack = second;
    second->prev = NULL;
    free(first);
}
```

### Update monty.h
Add the prototypes for the new functions to the header file.

```c
void monty_div(stack_t **stack, unsigned int line_number);
void monty_mul(stack_t **stack, unsigned int line_number);
void monty_mod(stack_t **stack, unsigned int line_number);
```

### Update instructions Array in monty.c
Modify the instructions array in the main file to include the `div`, `mul`, and `mod` opcodes.

```c
instruction_t instructions[] = {
    {"push", monty_push},
    {"pall", monty_pall},
    {"pint", monty_pint},
    {"pop", monty_pop},
    {"swap", monty_swap},
    {"add", monty_add},
    {"sub", monty_sub},
    {"div", monty_div},
    {"mul", monty_mul},
    {"mod", monty_mod},
    {"nop", monty_nop},
    {NULL, NULL}
};
```

### Summary of Changes
1. **`monty_div.c`**: Implemented the `monty_div` function to divide the second top element by the top element and handle division by zero.
2. **`monty_mul.c`**: Implemented the `monty_mul` function to multiply the second top element with the top element.
3. **`monty_mod.c`**: Implemented the `monty_mod` function to compute the remainder of the division of the second top element by the top element and handle division by zero.
4. **Updated `monty.h`**: Added function prototypes for the new opcodes.
5. **Updated `monty.c`**: Added the new opcodes to the instructions array.

### Compilation
You can compile the code as before:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=c89 *.c -o monty
```

Now the Monty interpreter can handle the `div`, `mul`, and `mod` opcodes. When invoked, they will perform the respective operations and handle errors appropriately.


Here’s how to implement the `pchar`, `pstr`, `rotl`, and `rotr` opcodes, along with updates for the stack and queue functionality. Each opcode will be implemented in its own file, and I’ll detail the changes needed.

### monty_pchar.c
Create a new file for the `pchar` opcode implementation.

```c
#include "monty.h"
#include <stdio.h>

/**
 * monty_pchar - Opcode to print the char at the top of the stack
 * @stack: Pointer to the top of the stack
 * @line_number: Position in code we are working
 */
void monty_pchar(stack_t **stack, unsigned int line_number) {
    if (!stack || !*stack) {
        monty_handle_error("can't pchar, stack empty", NULL, line_number);
    }

    if ((*stack)->n < 0 || (*stack)->n > 127) {
        monty_handle_error("can't pchar, value out of range", NULL, line_number);
    }

    printf("%c\n", (*stack)->n);
}
```

### monty_pstr.c
Create a new file for the `pstr` opcode implementation.

```c
#include "monty.h"
#include <stdio.h>

/**
 * monty_pstr - Opcode to print the string starting at the top of the stack
 * @stack: Pointer to the top of the stack
 * @line_number: Position in code we are working
 */
void monty_pstr(stack_t **stack, unsigned int line_number) {
    stack_t *current = *stack;

    (void)line_number; // Unused parameter

    while (current && current->n) {
        if (current->n < 1 || current->n > 127) {
            break;
        }
        printf("%c", current->n);
        current = current->next;
    }
    printf("\n");
}
```

### monty_rotl.c
Create a new file for the `rotl` opcode implementation.

```c
#include "monty.h"

/**
 * monty_rotl - Opcode to rotate the stack to the top
 * @stack: Pointer to the top of the stack
 * @line_number: Position in code we are working
 */
void monty_rotl(stack_t **stack, unsigned int line_number) {
    stack_t *top;

    (void)line_number; // Unused parameter

    if (!stack || !*stack || !(*stack)->next) {
        return; // No rotation needed if stack is empty or has one element
    }

    top = *stack;
    *stack = top->next;
    (*stack)->prev = NULL;

    top->next = NULL;
    stack_t *current = *stack;

    while (current->next) {
        current = current->next;
    }
    current->next = top;
    top->prev = current;
}
```

### monty_rotr.c
Create a new file for the `rotr` opcode implementation.

```c
#include "monty.h"

/**
 * monty_rotr - Opcode to rotate the stack to the bottom
 * @stack: Pointer to the top of the stack
 * @line_number: Position in code we are working
 */
void monty_rotr(stack_t **stack, unsigned int line_number) {
    stack_t *bottom;

    (void)line_number; // Unused parameter

    if (!stack || !*stack || !(*stack)->next) {
        return; // No rotation needed if stack is empty or has one element
    }

    bottom = *stack;
    while (bottom->next) {
        bottom = bottom->next;
    }

    bottom->next = *stack;
    (*stack)->prev = bottom;
    *stack = bottom;
    bottom->next->prev = NULL;
    bottom->next->next = NULL; // Update the new last element
}
```

### Update monty.h
Add the prototypes for the new functions to the header file.

```c
void monty_pchar(stack_t **stack, unsigned int line_number);
void monty_pstr(stack_t **stack, unsigned int line_number);
void monty_rotl(stack_t **stack, unsigned int line_number);
void monty_rotr(stack_t **stack, unsigned int line_number);
```

### Update instructions Array in monty.c
Modify the instructions array in the main file to include the new opcodes.

```c
instruction_t instructions[] = {
    {"push", monty_push},
    {"pall", monty_pall},
    {"pint", monty_pint},
    {"pop", monty_pop},
    {"swap", monty_swap},
    {"add", monty_add},
    {"sub", monty_sub},
    {"div", monty_div},
    {"mul", monty_mul},
    {"mod", monty_mod},
    {"pchar", monty_pchar},
    {"pstr", monty_pstr},
    {"rotl", monty_rotl},
    {"rotr", monty_rotr},
    {"nop", monty_nop},
    {"stack", monty_stack},
    {"queue", monty_queue},
    {NULL, NULL}
};
```

### Implementing stack and queue opcodes
You’ll need to implement the `stack` and `queue` opcodes to switch between the two data structures.

### monty_stack.c
Create a new file for the `stack` opcode implementation.

```c
#include "monty.h"

/**
 * monty_stack - Opcode to set the format to stack (LIFO)
 * @stack: Pointer to the top of the stack
 * @line_number: Position in code we are working
 */
void monty_stack(stack_t **stack, unsigned int line_number) {
    (void)stack;      // Unused parameter
    (void)line_number; // No action needed, set default format
    // This is the default behavior, no changes required.
}
```

### monty_queue.c
Create a new file for the `queue` opcode implementation.

```c
#include "monty.h"

/**
 * monty_queue - Opcode to set the format to queue (FIFO)
 * @stack: Pointer to the top of the stack
 * @line_number: Position in code we are working
 */
void monty_queue(stack_t **stack, unsigned int line_number) {
    (void)stack;      // Unused parameter
    (void)line_number; // No action needed
}
```

### Summary of Changes
1. **Implemented `pchar`**: Prints the ASCII character at the top of the stack.
2. **Implemented `pstr`**: Prints the string starting at the top of the stack.
3. **Implemented `rotl`**: Rotates the stack to the top.
4. **Implemented `rotr`**: Rotates the stack to the bottom.
5. **Implemented `stack`**: Sets the format to stack (LIFO).
6. **Implemented `queue`**: Sets the format to queue (FIFO).
7. **Updated `monty.h`**: Added function prototypes for the new opcodes.
8. **Updated `monty.c`**: Added the new opcodes to the instructions array.

### Compilation
You can compile the code as before:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=c89 *.c -o monty
```

Now the Monty interpreter can handle the `pchar`, `pstr`, `rotl`, `rotr`, `stack`, and `queue` opcodes.


To implement the functionality of ignoring comment lines in the Monty interpreter, you need to modify the part of your code that reads the lines from the Monty bytecode file. Specifically, you'll want to check if the first non-space character of a line is `#` and skip processing those lines.

Here’s how to do this:

### Update Your Line Reading Logic
Locate the section of your code where you read the lines from the Monty bytecode file. Modify it to check for comment lines.

Assuming you have a function that processes each line of the bytecode, here’s an example of how you could implement this.

### Example Code for Processing Lines
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

void process_line(char *line, unsigned int line_number, stack_t **stack) {
    char *opcode;
    char *arg;

    // Ignore comment lines
    if (line[0] == '#' || (line[0] == '\0' && isspace(line[1]))) {
        return; // Skip comments and empty lines
    }

    // Tokenize the line to get the opcode and argument
    opcode = strtok(line, " \n");
    arg = strtok(NULL, " \n");

    if (opcode) {
        // Find the corresponding function for the opcode and execute it
        int found = 0;
        for (int i = 0; instructions[i].opcode; i++) {
            if (strcmp(instructions[i].opcode, opcode) == 0) {
                found = 1;
                instructions[i].f(stack, line_number);
                break;
            }
        }
        if (!found) {
            fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
            exit(EXIT_FAILURE);
        }
    }
}
```

### Incorporate the Change
1. **Ignore Comments**: The `process_line` function checks if the line starts with `#` or is empty and skips processing if it does.
2. **Tokenize the Line**: The line is tokenized to separate the opcode and any arguments.
3. **Instruction Lookup**: The function searches for the opcode in the instruction set and executes the corresponding function.

### Usage in Main Loop
Ensure that this line processing function is called correctly in your main loop where you read from the bytecode file:

```c
FILE *file = fopen(argv[1], "r");
char *line = NULL;
size_t len = 0;
unsigned int line_number = 0;

while (getline(&line, &len, file) != -1) {
    line_number++;
    process_line(line, line_number, &stack);
}

free(line);
fclose(file);
```

### Summary
1. **Comment Handling**: Lines starting with `#` are ignored during processing.
2. **Robustness**: The code handles empty lines and comments gracefully.
3. **No Changes to Structs**: The existing structs and functions remain unchanged.

### Compilation
Compile as usual:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=c89 *.c -o monty
```

Now, the Monty interpreter will properly ignore comment lines, allowing for clearer and more organized code in your bytecode files.

***I dont have a function that reads the bytecode***
If you don't have a dedicated function to read the bytecode, you can incorporate the line reading and processing directly in your `main` function. Here's how you can modify your `main` function to read lines from the file, ignore comments, and process the opcodes accordingly.

### Example of Modifying the Main Function

Assuming your `main` function is set up to accept the bytecode file, here’s how to implement the reading and processing:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

int main(int argc, char *argv[]) {
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    stack_t *stack = NULL;  // Your stack initialization
    unsigned int line_number = 0;

    if (argc != 2) {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (getline(&line, &len, file) != -1) {
        line_number++;
        
        // Ignore comment lines
        if (line[0] == '#' || (line[0] == '\n')) {
            continue;
        }

        char *opcode = strtok(line, " \n");
        char *arg = strtok(NULL, " \n");

        if (opcode) {
            // Find and execute the corresponding opcode function
            int found = 0;
            for (int i = 0; instructions[i].opcode; i++) {
                if (strcmp(instructions[i].opcode, opcode) == 0) {
                    found = 1;
                    instructions[i].f(&stack, line_number);
                    break;
                }
            }
            if (!found) {
                fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
                free(line);
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }

    free(line);
    fclose(file);
    return (EXIT_SUCCESS);
}
```

### Breakdown of the Implementation
1. **File Handling**: The program opens the specified bytecode file and checks for errors.
2. **Line Reading**: It reads the file line by line using `getline()`.
3. **Comment Ignoring**: Lines starting with `#` or empty lines are ignored.
4. **Opcode Processing**: Each valid line is tokenized to extract the opcode and its argument.
5. **Opcode Execution**: The program checks for the opcode in the `instructions` array and executes the corresponding function.
6. **Error Handling**: If an unknown opcode is encountered, an error message is printed, and the program exits.

### Compilation
Compile your code as usual:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=c89 *.c -o monty
```

### Summary
This setup provides a simple and effective way to read and process Monty bytecode while ignoring comments.

***what does this error code mean? `control reaches end of non-void function`***
The error message "control reaches end of non-void function" means that your function, which is expected to return a value (because it is declared with a non-void return type), does not have a return statement that guarantees a value is returned in all possible execution paths.

### Example of the Error

Consider the following function:

```c
int example_function(int x) {
    if (x > 0) {
        return x;
    }
    // No return statement here if x <= 0
}
```

In this case, if `x` is less than or equal to 0, the function reaches the end without hitting a `return` statement, which causes the compiler to issue the error.

### How to Fix It

To resolve this error, ensure that all code paths in your non-void function return a value. Here’s how you might fix the previous example:

```c
int example_function(int x) {
    if (x > 0) {
        return x;
    }
    return 0; // Provide a return value for the case when x <= 0
}
```

### General Tips
1. **Return Statements**: Make sure every conditional branch in your function leads to a return statement.
2. **Default Return**: If necessary, provide a default return statement at the end of the function.
3. **Check Logic**: Review your function logic to ensure that all paths are accounted for, especially in conditional statements.

### Example in Context

If you have a function like this:

```c
int monty_push(stack_t **stack, unsigned int line_number) {
    // Logic to push an element onto the stack
    // Missing return statement here
}
```

You should add a return statement, for example:

```c
int monty_push(stack_t **stack, unsigned int line_number) {
    // Logic to push an element onto the stack
    return 0; // Or appropriate return value based on your function logic
}
```

### Summary
Ensure that every non-void function has a return statement for every possible execution path to avoid the "control reaches end of non-void function" error.



Certainly! A comprehensive test suite for the Monty interpreter should cover various scenarios to ensure that all opcodes work correctly, handle errors appropriately, and manage edge cases. Here’s a breakdown of the test suite, including test cases and expected outcomes.

### Directory Structure
First, organize your tests. You might create a directory called `tests` with individual test files for each opcode and a main test script.

### Sample Test Files

#### 1. `tests/test_push.m`
```plaintext
push 5
push 10
pall
```
**Expected Output:**
```
10
5
```

#### 2. `tests/test_pint.m`
```plaintext
push 42
pint
```
**Expected Output:**
```
42
```

#### 3. `tests/test_pop.m`
```plaintext
push 1
push 2
pop
pall
```
**Expected Output:**
```
1
```

#### 4. `tests/test_swap.m`
```plaintext
push 1
push 2
swap
pall
```
**Expected Output:**
```
2
1
```

#### 5. `tests/test_add.m`
```plaintext
push 3
push 5
add
pall
```
**Expected Output:**
```
8
```

#### 6. `tests/test_sub.m`
```plaintext
push 10
push 5
sub
pall
```
**Expected Output:**
```
5
```

#### 7. `tests/test_div.m`
```plaintext
push 10
push 2
div
pall
```
**Expected Output:**
```
5
```

#### 8. `tests/test_mul.m`
```plaintext
push 2
push 3
mul
pall
```
**Expected Output:**
```
6
```

#### 9. `tests/test_mod.m`
```plaintext
push 10
push 3
mod
pall
```
**Expected Output:**
```
1
```

#### 10. `tests/test_pchar.m`
```plaintext
push 65
pchar
```
**Expected Output:**
```
A
```

#### 11. `tests/test_pstr.m`
```plaintext
push 72
push 101
push 108
push 108
push 111
push 0
pstr
```
**Expected Output:**
```
Hello
```

#### 12. `tests/test_rotl.m`
```plaintext
push 1
push 2
push 3
rotl
pall
```
**Expected Output:**
```
2
3
1
```

#### 13. `tests/test_rotr.m`
```plaintext
push 1
push 2
push 3
rotr
pall
```
**Expected Output:**
```
3
1
2
```

#### 14. `tests/test_stack.m`
```plaintext
stack
push 1
push 2
pall
```
**Expected Output:**
```
2
1
```

#### 15. `tests/test_queue.m`
```plaintext
queue
push 1
push 2
pall
```
**Expected Output:**
```
1
2
```

#### 16. `tests/test_error.m`
```plaintext
push 1
push two
```
**Expected Output:**
```
L2: usage: push integer
```

#### 17. `tests/test_empty_stack_pop.m`
```plaintext
pop
```
**Expected Output:**
```
L1: can't pop an empty stack
```

### Main Test Script
Create a script to automate running these tests. For example, in `tests/run_tests.sh`:

```bash
#!/bin/bash

for test in tests/*.m; do
    echo "Running $test..."
    output=$(./monty "$test" 2>&1)
    echo "$output"
    echo "-----------------------"
done
```

### Usage
1. Create a `tests` directory and place your test `.m` files and the `run_tests.sh` script inside it.
2. Ensure your Monty interpreter is compiled as `monty`.
3. Run the test script:
   ```bash
   chmod +x tests/run_tests.sh
   ./tests/run_tests.sh
   ```

### Summary
This test suite covers the essential functionality of the Monty interpreter, including all opcodes and error handling. You can expand upon these tests as needed to cover additional edge cases or specific scenarios.


To handle malformed commands, such as `push - 1024` and `push 123a`, you'll need to implement additional validation in your opcode processing logic. Here's how you can do that:

### Steps to Enhance Validation

1. **Check for Invalid Tokens**: After splitting the command into the opcode and its argument, you need to ensure that the argument is a valid integer.

2. **Handle Malformed Input**: When parsing the argument, check for extra spaces or invalid characters.

3. **Use `strtol` for Integer Conversion**: This function allows you to check if the conversion was successful and whether the entire string was valid.

### Example Code Modifications

Here’s how you could implement these checks in your `process_line` function:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "monty.h"

void process_line(char *line, unsigned int line_number, stack_t **stack) {
    char *opcode;
    char *arg;

    // Ignore comment lines
    if (line[0] == '#' || (line[0] == '\n')) {
        return; // Skip comments and empty lines
    }

    // Tokenize the line to get the opcode and argument
    opcode = strtok(line, " \n");
    arg = strtok(NULL, " \n");

    if (opcode) {
        // Find the corresponding function for the opcode
        int found = 0;
        for (int i = 0; instructions[i].opcode; i++) {
            if (strcmp(instructions[i].opcode, opcode) == 0) {
                found = 1;

                // Handle push arguments
                if (strcmp(opcode, "push") == 0) {
                    if (arg == NULL) {
                        fprintf(stderr, "L%d: usage: push integer\n", line_number);
                        exit(EXIT_FAILURE);
                    }

                    char *endptr;
                    long value = strtol(arg, &endptr, 10);

                    if (*endptr != '\0' || endptr == arg) {
                        fprintf(stderr, "L%d: usage: push integer\n", line_number);
                        exit(EXIT_FAILURE);
                    }

                    // Valid push value, call the push function
                    // You would need to modify the push function to take 'value'
                    monty_push(stack, line_number, value);
                } else {
                    instructions[i].f(stack, line_number);
                }
                break;
            }
        }

        if (!found) {
            fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
            exit(EXIT_FAILURE);
        }
    }
}
```

### Explanation of the Changes

1. **Argument Check**: After finding the opcode, if it's `push`, the code checks if `arg` is `NULL` (which means no argument was provided). If so, it outputs an error message.

2. **Using `strtol`**: This function converts the string to a long integer. It also allows checking if the conversion was successful:
   - `endptr` points to the first invalid character after the number. If it points to the same position as `arg` or if it's not pointing to the end of the string (`*endptr != '\0'`), it indicates that the input was not a valid integer.

3. **Calling the Push Function**: You may need to modify your `monty_push` function to accept an integer value rather than expecting it from the global or stack context.

### Example `monty_push` Function

You might also need to modify your `monty_push` function like this:

```c
/**
 * monty_push - Opcode to push
 * @stack: pointer to the top of a stack
 * @line_number: position in code we are working
 * @value: integer value to push
 */
void monty_push(stack_t **stack, unsigned int line_number, int value) {
    stack_t *new_node = malloc(sizeof(stack_t));
    if (!new_node) {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->n = value;
    new_node->next = *stack;
    new_node->prev = NULL;

    if (*stack) {
        (*stack)->prev = new_node;
    }
    *stack = new_node;
}
```