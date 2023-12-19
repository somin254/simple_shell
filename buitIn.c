#include "main.h"

/**
 * _atoi - convert a string to an integer.
 * @s: char type string
 * Return: integer converted
 */

int _atoi(char *s)
{
	int i;
	int result = 0;
	int sign = -1;
	int brk = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '-')
			sign = sign * -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			result = result * 10;
			result -= (s[i] - '0');
			brk = 1;
		}
		else if (brk == 1)
			break;
	}
	result = sign * result;
	return (result);
}

/**
 * execute_exit - handles built in exit
 * @array: array of the input from user
 * @command: for freeing
 *
 * Return: Nothing
 */

void execute_exit(char **array, char *command)
{
	int status;

	if (array[1] != NULL)
	{
		status = _atoi(array[1]);
		if (status == 0 && *array[1] != '0')
		{
			write(STDERR_FILENO, "./hsh: 1: exit: Illegal number: ", 34);
			write(STDERR_FILENO, array[1], _strlen(array[0]));
			write(STDERR_FILENO, "\n", 1);
			free(command);
			free(array);
			exit(2);
		}
		free(command);
		free(array);
		exit(status);
	}
	else
	{
		free(command);
		free(array);
		exit(0);
	}
}

/**
 * execute_env - handles env
 *
 * Return: Nothing
 */

void execute_env(void)
{
	int i = 0;
	char **env = environ;

	while (env[i])
	{
		write(STDOUT_FILENO, (const void *)env[i], _strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
