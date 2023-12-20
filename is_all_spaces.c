#include "main.h"
#include <ctype.h> /* Include for isspace function */

/**
 * is_all_spaces - checks whether a given string is composed of only spaces
 * @str: pointer to a string to be checked
 *
 * Return: false if the string is not all spaces and true otherwise
 */

bool is_all_spaces(const char *str)
{
    while (*str != '\0')
    {
        if (!isspace((unsigned char)*str))
            return false;
        str++;
    }
    return true;
}

/**
 * check_line - checks line
 * @line_size: a No
 * @command: string from getline function
 *
 * Return: Nothing
 */

void check_line(ssize_t line_size, char *command)
{
    if (line_size == -1 || line_size == EOF)
    {
        free(command);
        exit(EXIT_SUCCESS);
    }
}

/**
 * end_of_file - executes ctrl d
 * @array: pointer to an array of strings
 *
 * Return: Nothing;
 */

void end_of_file(char **array)
{
    (void)array;
    exit(EXIT_SUCCESS);
}

