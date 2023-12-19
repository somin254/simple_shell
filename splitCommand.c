#include "main.h"

/**
 * split_command - splits the commands entered by the user
 * @string: commands entered by user
 *
 * Return: pointer to a pointer of words
 */

char **split_command(char *string)
{
	char **result = malloc(sizeof(char *) * _strlen(string));
	char *token = _strtok(string, " ");
	int i = 0;

	if (result == NULL)
	{
		perror("Error allocating memory");
		free(result);
		exit(EXIT_FAILURE);
	}
	while (token != NULL)
	{
		result[i++] = token;
		token = _strtok(NULL, " ");
	}
	result[i] = NULL;
	return (result);
}
