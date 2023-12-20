#include "main.h"

/**
 * _str_char - Locate character in a string
 * @str: String
 * @c: Character
 *
 * Return: Pointer to @c else NULL if no match is found
 */
char *_str_char(const char *str, int c)
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
 * _str_token - Separate a sentence
 * @str: Pointer to the sentence
 * @delim: String containing characters that separate the tokens
 *
 * Return: Pointer to an array
 */
char *_str_token(char *str, char *delim)
{
	static char *next_token;
	char *token;

	if (str != NULL)
	{
		next_token = str;
	}
	if (next_token == NULL || *next_token == '\0')
	{
		return (NULL);
	}
	while (*next_token != '\0' && _str_char(delim, *next_token) != NULL)
	{
		next_token++;
	}
	if (*next_token == '\0')
	{
		return (NULL);
	}

	token = next_token;

	while (*next_token != '\0' && _str_char(delim, *next_token) == NULL)
	{
		next_token++;
	}
	if (*next_token != '\0')
	{
		*next_token = '\0';
		next_token++;
	}
	return (token);
}
