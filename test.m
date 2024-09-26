# Sample Monty bytecode file

push 5      # Pushes 5 onto the stack
push 10     # Pushes 10 onto the stack
push 3      # Pushes 3 onto the stack
pall        # Prints all elements (3, 10, 5)
add         # Adds top two elements (3 + 10 = 13), new top: 13
pint        # Prints the top element (13)
push 8      # Pushes 8 onto the stack
pall
sub         # Subtracts top two elements (13 - 8 = 5), new top: 5
pall        # Prints all elements (5, 5)
push 2      # Pushes 2 onto the stack
mul         # Multiplies top two elements (5 * 2 = 10), new top: 10
pall        # Prints all elements (10, 5)
push 4      # Pushes 4 onto the stack
div         # Divides second top element by the top (10 / 4 = 2), new top: 2
pall        # Prints all elements (2, 5)
push 7      # Pushes 7 onto the stack
mod         # Modulo of second top element by top (5 % 7 = 5), new top: 5
pall        # Prints all elements (5, 2)
pchar       # Prints the char at the top of the stack (ASCII 5 -> Error)
nop         # Does nothing
