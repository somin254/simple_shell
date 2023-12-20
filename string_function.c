#include "main.h"

/**
 * _str_length - Counts the length of a string and returns the number
 * @str: String whose length is to be determined
 *
 * Return: Length of the string
 */
int _str_length(const char *str)
{
	int len = 0;

	while (*str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}

/**
 * _str_compare - Compares two strings
 * @s1: One of the strings
 * @s2: The other string
 * @n: Length to use in comparison
 *
 * Return: 0 if s1 and s2 are the same, negative number if s2 < s1,
 * positive number otherwise
 */
int _str_compare(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
	}
	return (0);
}

/**
 * _str_copy - Copies one string to another
 * @dest: Where the string is to be copied to
 * @src: Where the string is to be copied from
 *
 * Return: Nothing
 */
void _str_copy(char *dest, const char *src)
{
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}

/**
 * _str_concat - Concatenates two strings
 * @dest: String to which another string is to be added
 * @src: Source of the string to be concatenated
 *
 * Return: Nothing
 */
void _str_concat(char *dest, const char *src)
{
	while (*dest != '\0')
	{
		dest++;
	}
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}
