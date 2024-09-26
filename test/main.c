#include "main.h"

/**
 * main - entry into main
 * @argc: arguments
 * @argv: pointer to arguments
 * 
 * Return: 0
 */
int main(int argc, char *argv[])
{
    FILE *file;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    execute_file(file);

    fclose(file);

    return 0;
}
