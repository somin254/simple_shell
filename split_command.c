#include "main.h"

/**
 * split_command - Splits the commands entered by the user
 * @input_string: Commands entered by the user
 *
 * Return: Pointer to a pointer of words
 */
char **split_command(char *input_string)
{
	char **result = malloc(sizeof(char *) * _strlen(input_string));
	char *token = _strtok(input_string, " ");
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
