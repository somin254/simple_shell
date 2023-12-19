#include "main.h"

/**
 * _strchr - loacate character in string
 * @str: string
 * @c: character
 * Return: pointer to @c else NULL if no match is not found
 */

char *_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}

/**
 * _strtok - separate a sentence
 * @str: pointer to the sentence
 * @delim: what separates the string
 *
 * Return: pointer to an array
 */

char *_strtok(char *str, char *delim)
{
	static char *nextToken;
	char *token;

	if (str != NULL)
	{
		nextToken = str;
	}
	if (nextToken == NULL || *nextToken == '\0')
	{
		return (NULL);
	}
	while (*nextToken != '\0' && _strchr(delim, *nextToken) != NULL)
	{
		nextToken++;
	}
	if (*nextToken == '\0')
	{
		return (NULL);
	}

	token = nextToken;

	while (*nextToken != '\0' && _strchr(delim, *nextToken) == NULL)
	{
		nextToken++;
	}
	if (*nextToken != '\0')
	{
		*nextToken = '\0';
		nextToken++;
	}
	return (token);
}
