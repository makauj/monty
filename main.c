#include "main.h"

/**
 * main - entry into main
 * @argv: arguments
 * @argc: arguments
 *
 * Return: 0
 */

int main(int argc, char *argv[])
{
    char *command = NULL;
    size_t len = 0;
    int line_number = 1;
    char *token, *endptr;
    long value;

    while (getline(&command, &len, stdin) != -1)
    {
        token = strtok(command, " \n");
        if (token == NULL)
        {
            line_number++;
            continue;
        }

        if (strcmp(token, "push") == 0)
        {
            token = strtok(NULL, " \n");
            if (token == NULL)
            {
                error_exit("usage: push integer", line_number);
            }

            value = strtol(token, &endptr, 10);
            if (*endptr != '\0')
            {
                error_exit("usage: push integer", line_number);
            }

            push((int)value);
        }
        else if (strcmp(token, "pall") == 0)
        {
            pall();
        }
        else
        {
            error_exit("unknown instruction", line_number);
        }

        line_number++;
    }

    free(command);
    free_stack();
    return (0);
}