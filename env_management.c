#include "shell.h"

/**
 * env_get_key - gets the value of an environment variable
 * @key: the environment variable of interest
 * @data: struct of the program's data
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */
char *env_get_key(char *key, data_of_program *data)
{
	int index, key_length = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* obtains the length of the variable requested */
	key_length = str_length(key);

	for (index = 0; data->env[index]; index++)
	{
		/* Iterates through the environ and checks for coincidence of the name */
		if (str_compare(key, data->env[index], key_length) &&
			data->env[index][key_length] == '=')
		{
			/* returns the value of the key NAME= when found */
			return (data->env[index] + key_length + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);
}

/**
 * env_set_key - overwrite the value of the environment variable
 * or create it if does not exist.
 * @key: name of the variable to set
 * @value: new value
 * @data: struct of the program's data
 * Return: 1 if the parameters are NULL, 2 if there is an error or 0 if success.
 */
int env_set_key(char *key, char *value, data_of_program *data)
{
	int index, key_length = 0, is_new_key = 1;

	/* validate the arguments */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* obtains the length of the variable requested */
	key_length = str_length(key);

	for (index = 0; data->env[index]; index++)
	{
		/* Iterates through the environ and checks for coincidence of the name */
		if (str_compare(key, data->env[index], key_length) &&
			data->env[index][key_length] == '=')
		{
			/* If key already exists */
			is_new_key = 0;
			/* free the entire variable, it is newly created below */
			free(data->env[index]);
			break;
		}
	}
	/* make a string of the form key=value */
	data->env[index] = str_concat(str_duplicate(key), "=");
	data->env[index] = str_concat(data->env[index], value);

	if (is_new_key)
	{
		/* if the variable is new, it is created at the end of the current list */
		/* and we need to put the NULL value in the next position */
		data->env[index + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - remove a key from the environment
 * @key: the key to remove
 * @data: the structure of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int env_remove_key(char *key, data_of_program *data)
{
	int index, key_length = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (0);

	/* obtains the length of the variable requested */
	key_length = str_length(key);

	for (index = 0; data->env[index]; index++)
	{
		/* iterates through the environ and checks for coincidences */
		if (str_compare(key, data->env[index], key_length) &&
			data->env[index][key_length] == '=')
		{
			/* if key already exists, remove it */
			free(data->env[index]);

			/* move the other keys one position down */
			index++;
			for (; data->env[index]; index++)
			{
				data->env[index - 1] = data->env[index];
			}
			/* put the NULL value at the new end of the list */
			data->env[index - 1] = NULL;
			return (1);
		}
	}
	return (0);
}

/**
 * print_environ - prints the current environ
 * @data: struct for the program's data
 * Return: nothing
 */
void print_environ(data_of_program *data)
{
	int index;

	for (index = 0; data->env[index]; index++)
	{
		_print(data->env[index]);
		_print("\n");
	}
}
