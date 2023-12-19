#include "main.h"

/**
 * main - initiates the program
 * @ac: no use in the program
 * @argv: no use in the program
 * @envp: helps in implementing clear command
 *
 * Return: int to show succces in implimenting the program
 */

int main(int ac, char *argv[], char *envp[])
{
	char *command = NULL;
	size_t len = 0;
	char **array = NULL;
	ssize_t line_size = 0;

	(void)argv;
	(void)ac;
	(void)envp;
	while (1)
	{
		prompt();
		line_size = getline(&command, &len, stdin);
		check_line(line_size, command);
		if (line_size <= 0)
			break;
		if (is_all_spaces(command))
			continue;
		if (command[line_size - 1] == '\n')
			command[line_size - 1] = '\0';
		if (command[0] == '\n' || command[0] == '\0')
			continue;
		array = split_command(command);
		if (array == NULL)
		{
			perror("Error splitting command.");
			free(command);
			exit(EXIT_FAILURE);
		}
		if (_strncmp(array[0], "exit", 4) == 0)
			execute_exit(array, command);
		if (_strncmp(array[0], "env", 3) == 0)
		{
			free(command);
			free(array);
			execute_env();
			break;
		}
		else
			execute(array, (char *const *)envp);
		free(array); }
	return (0); }
