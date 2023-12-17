#include "shell.h"

/**
 * interactive - checks if the shell is in interactive mode
 * @infos: struct containing information
 *
 * Return: 1 if in interactive mode, otherwise 0
 */
int interactive(info_t *infos)
{
	return (isatty(STDIN_FILENO) && infos->readfd <= 2);
}

/**
 * _isalpha - checks if a character is alphabetic
 * @ch: character to check
 *
 * Return: 1 if @ch is alphabetic, 0 otherwise
 */
int _isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @str: string to convert
 *
 * Return: converted integer, or 0 if no numbers in the string
 */
int _atoi(char *str)
{
	int z, signs = 1, flags = 0, outputs;
	unsigned int result = 0;

	for (z = 0; str[z] != '\0' && flags != 2; z++)
	{
		if (str[z] == '-')
			signs *= -1;
		if (str[z] >= '0' && str[z] <= '9')
		{
			flags = 1;
			result *= 10;
			result += (str[z] - '0');
		}
		else if (flags == 1)
			flags = 2;
	}
	if (signs == -1)
		outputs = -result;
	else
		outputs = result;
	return (outputs);
}

/**
 * is_delim - checks if a character is a delimiter
 * @ch: character to check
 * @delime: delimiter string
 *
 * Return: 1 if @ch is a delimiter, 0 otherwise
 */
int is_delim(char ch, char *delime)
{
	while (*delime)
		if (*delime++ == ch)
			return (1);
	return (0);
}

