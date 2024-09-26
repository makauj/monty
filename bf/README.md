# Brainfuck

This is an Esoteric programming language, with unique data representations and instructions representation. Such languages are difficult to read and write.
Brainfuck was created by Urban Muller in 1993 with eight simple commands, a data pointer and an instruction pointer.

## Language Commands
|Character | Meaning |
|--- | ---|
| > | Increment the data pointer by one (to point to the next cell to the right) |
| < | Decrement the data pointer by one (to point to the next cell to the left) |
| + | Increment the byte at the data pointer by one |
| - | Decrement the byte at the data pointer by one |
| . | Output the byte at the data pointer |
| , | Accept one byte of input, storing its value in the byte at the data pointer |
| [ | If the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command |
| ] | If the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command |

## Simple Examples

### Add two values
```
[->+<]
```
```
++       Cell c0 = 2
> +++++  Cell c1 = 5

[        Start your loops with your cell pointer on the loop counter (c1 in our case)
< +      Add 1 to c0
> -      Subtract 1 from c1
]        End your loops with the cell pointer on the loop counter

At this point our program has added 5 to 2 leaving 7 in c0 and 0 in c1
but we cannot output this value to the terminal since it is not ASCII encoded

To display the ASCII character "7" we must add 48 to the value 7
We use a loop to compute 48 = 6 * 8

++++ ++++  c1 = 8 and this will be our loop counter again
[
< +++ +++  Add 6 to c0
> -        Subtract 1 from c1
]
< .        Print out c0 which has the value 55 which translates to "7"!
```

### Multiply two digits given by the User

**The code**

```brainfuck
,>++++++[<-------->-],[<->++<]>>++++++++++>++++++++++>++++++++++++[->++++++++++<]>>>.
```
### Code Breakdown
**Read the input**
```
,
```
- This command reads a single character from standard input `stdin` and stores it in the current cell.

**Setting up the second input**
```brainfuck
>++++++[<-------->-],
```
- Move to the next cell `(>)`.
- Set up the loop to adjust the first digit read into a usable range for multiplication. The `++++++[<-------->-]` part subtracts 48 (the ASCII value for '0') from the input, effectively converting the character representation of the digit into its integer value.
- Read the second digit with the , command.

**Prepare for multiplication**
```brainfuck
[<->++<]
```
- This section transfers the first digit into separate areas for manipulation. This also ensures proper adjustment for he digits.

**Multiplying**
```brainfuck
>>++++++++++>++++++++++>++++++++++++[->++++++++++<]
```
- Move to an area to set up a counter for multiplication.
- The `++++++++++` sections initialize cells for the multiplication process.
- The loop `[->++++++++++<]` takes care of multiplying the digits. This uses a nested loop structure where the value of one digit gets added to another cell based on the value of the second digit.

**Output the result**
```
>>.
```
- Move to the cell with the result and print it. The `.` command outputs the value of the current cell as a character.
## Where is Brainfuck used?
1. Educational Purposes:

	- It teaches concepts of memory manipulation and how a Turing machine works, making it a fun way to understand low-level computing.

2. Challenge and Competition:

	- Many programming competitions or challenges include Brainfuck to test problem-solving skills and creativity in a constrained environment.

3. Obfuscation:

	- It can be used to write code that is intentionally hard to read, either for fun or as a part of a puzzle.

4. Art and Aesthetics:

	- Some programmers write Brainfuck code as a form of digital art, where the aesthetic of the code itself is a part of the expression.

5. Learning Tool:

	- It serves as a gateway to understand more complex programming concepts in a simplified format.

While Brainfuck is not practical for real-world applications, it showcases the fundamentals of computation and memory management in a unique way!

# References
[wikipedia](https://en.wikipedia.org/wiki/Brainfuck)

