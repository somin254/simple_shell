#include "shell.h"

/**
 * _erratoi - Converts string to int
 * @str: String to convert
 * Return: If no numbers in string (0) converted num, otherwise -1 on error
 */
int _erratoi(char *str)
{
	int z = 0;
	unsigned long int results = 0;

	if (*str == '+')
		str++;

	for (z = 0; str[z] != '\0'; z++)
	{
		if (str[z] >= '0' && str[z] <= '9')
		{
			results *= 10;
			results += (str[z] - '0');
			if (results > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (results);
}

/**
 * print_d - Prints a decimal int number (base 10)
 * @inputs: Input
 * @fd: Filedescriptor to write
 * Return: Number of characters printed
 */
int print_d(int inputs, int fd)
{
	int (*__putchar)(char) = _putchar;
	int z, counte = 0;
	unsigned int _ads_, currents;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;

	if (inputs < 0)
	{
		_ads_ = -inputs;
		__putchar('-');
		counte++;
	}
	else
		_ads_ = inputs;

	currents = _ads_;

	for (z = 1000000000; z > 1; z /= 10)
	{
		if (_ads_ / z)
		{
			__putchar('0' + currents / z);
			counte++;
		}
		currents %= z;
	}

	__putchar('0' + currents);
	counte++;
	return (counte);
}

/**
 * print_error - Prints error message
 * @infos: Parameter and return info struct
 * @est: String with specified type error
 * Return: If no numbers in string 0 converted number, otherwise -1 on error
 */
void print_error(info_t *infos, char *est)
{
	_eputs(infos->fname);
	_eputs(": ");
	print_d(infos->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(infos->argv[0]);
	_eputs(": ");
	_eputs(est);
}

/**
 * remove_comments - Replaces '#' with '\0'
 * @buffe: Address of string to modify
 * Return: Always (0)
 */
void remove_comments(char *buffe)
{
	int z;
	for (z = 0; buffe[z] != '\0'; z++)
		if (buffe[z] == '#' && (!z || buffe[z - 1] == ' '))
		{
			buffe[z] = '\0';
			break;
		}
}

/**
 * convert_number - Convert function clone of itoa
 * @numb: Number
 * @bases: Base
 * @flag: Argument flags
 * Return: A string
 */
char *convert_number(long int numb, int bases, int flag)
{
	static char *array;
	static char buffe[50];
	char sign = 0;
	char *ptdr;
	unsigned long b = numb;

	if (!(flag & CONVERT_UNSIGNED) && numb < 0)
	{
		b = -numb;
		sign = '-';
	}

	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptdr = &buffe[49];
	*ptdr = '\0';

	do {
		*--ptdr = array[b % bases];
		b /= bases;
	} while (b != 0);

	if (sign)
		*--ptdr = sign;

	return (ptdr);
}
