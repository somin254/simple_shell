#include "shell.h"

/**
 * read_input - read input from the prompt and split into commands.
 * @data: struct for the program's data
 * @buff: buffer to store input
 *
 * Return: reading counting bytes.
 */
static int read_input(data_of_program *data, char buff[BUFFER_SIZE])
{
	ssize_t bytes_read;
	size_t i = 0;

	if (!data->array_commands[0] ||
	    (data->array_operators[0] == '&' && errno != 0) ||
	    (data->array_operators[0] == '|' && errno == 0))
	{
		for (i = 0; data->array_commands[i]; i++)
		{
			free(data->array_commands[i]);
			data->array_commands[i] = NULL;
		}

		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		i = 0;
		do {
			data->array_commands[i] = str_duplicate(_strtok(i ? NULL : buff, "\n;"));
			i = check_logic_ops(data->array_commands, i, data->array_operators);
		} while (data->array_commands[i++]);
	}

	data->input_line = data->array_commands[0];
	for (i = 0; data->array_commands[i]; i++)
	{
		data->array_commands[i] = data->array_commands[i + 1];
		data->array_operators[i] = data->array_operators[i + 1];
	}

	return (str_length(data->input_line));
}

/**
 * _getline - read one line from the prompt.
 * @data: struct for the program's data
 *
 * Return: reading counting bytes.
 */
int _getline(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	return (read_input(data, buff));

}

/**
 * check_logic_ops - checks and split for && and || operators
 * @array_commands: array of the commands.
 * @i: index in the array_commands to be checked
 * @array_operators: array of the logical operators for each previous command
 *
 * Return: index of the last command in the array_commands.
 */
int check_logic_ops(char *array_commands[], int i, char array_operators[])
{
	char *temp = NULL;
	int j;

	for (j = 0; array_commands[i] != NULL && array_commands[i][j]; j++)
	{
		if (array_commands[i][j] == '&' && array_commands[i][j + 1] == '&')
		{
			temp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(temp + j + 2);
			i++;
			array_operators[i] = '&';
			free(temp);
			j = 0;
		}
		if (array_commands[i][j] == '|' && array_commands[i][j + 1] == '|')
		{
			temp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(temp + j + 2);
			i++;
			array_operators[i] = '|';
			free(temp);
			j = 0;
		}
	}

	return (i);
}
