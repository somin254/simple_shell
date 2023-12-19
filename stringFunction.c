#include "main.h"

/**
 * _strlen - counts the lenght of a string and returns the number
 * @str: string whose length is to be determined
 *
 * Return: length of the string
 */
int _strlen(const char *str)
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
 * _strncmp - compares two strings
 * @s1: one of the strings
 * @s2: the other string
 * @n: length to use in comparison
 *
 * Return: 0 if s1 & s2 are same, negative No is s2 < s1,
 * positive No otherwise
 */

int _strncmp(const char *s1, const char *s2, size_t n)
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
 * _strcpy - copies one string to another
 * @dest: where string is to be copied to
 * @src: where string is to be copied from
 *
 * Return: Nothing
 */

void _strcpy(char *dest, const char *src)
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
 * _strcat - concatenates two strings
 * @dest: string to be added another string
 * @src: source of string to be concatenated
 *
 * Return: Nothing
 */

void _strcat(char *dest, const char *src)
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
