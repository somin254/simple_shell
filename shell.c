#include "main.h"

/**
 * process_command - Handles the logic for different commands
 * @command_array: Array containing the command and its arguments
 * @input_command: The original input command
 * @envp: The environment variables
 */
void process_command(char **command_array, char *input_command, char *envp[])
{
	if (_strncmp(command_array[0], "exit", 4) == 0)
		execute_exit(command_array, input_command);

	if (_strncmp(command_array[0], "env", 3) == 0)
	{
		free(input_command);
		free(command_array);
		execute_env();
		exit(EXIT_SUCCESS);
	}
	else
		execute(command_array, (char *const *)envp);
}

/**
 * main - Initiates the program
 * @ac: No use in the program
 * @argv: No use in the program
 * @envp: Helps in implementing clear command
 *
 * Return: Int to show success in implementing the program
 */
int main(int ac, char *argv[], char *envp[])
{
	char *input_command = NULL;
	size_t input_length = 0;
	char **command_array = NULL;
	ssize_t line_size = 0;

	(void)argv;
	(void)ac;
	(void)envp;

	while (1)
	{
		prompt();
		line_size = getline(&input_command, &input_length, stdin);
		check_line(line_size, input_command);

		if (line_size <= 0)
			break;

		if (is_all_spaces(input_command))
			continue;

		if (input_command[line_size - 1] == '\n')
			input_command[line_size - 1] = '\0';

		if (input_command[0] == '\n' || input_command[0] == '\0')
			continue;

		command_array = split_command(input_command);

		if (command_array == NULL)
		{
			perror("Error splitting command.");
			free(input_command);
			exit(EXIT_FAILURE);
}
process_command(command_array, input_command, envp);
free(command_array);
}
free(input_command);
return (EXIT_SUCCESS);
}
