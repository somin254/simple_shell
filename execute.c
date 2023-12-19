#include "main.h"

/**
 * execute - shifts the process to execute another program
 * @array: list of the commands that are passed to the prompt
 * @environment: used in implementing clear command
 *
 * Return: Nothing
 */

void execute(char *array[], char *const *environment)
{
	int status;
	char *path, *token, command_path[1024];
	struct stat st;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Fork Failed!");
		exit(EXIT_FAILURE); }
	else if (pid == 0)
	{
		if (array[0][0] == '/' || array[0][0] == '.')
		{
			if (stat(array[0], &st) == 0 && S_ISREG(st.st_mode))
			{
				if (execve(array[0], array, environment) == -1)
				{
					perror("./shell");
					exit(EXIT_FAILURE); }}}
		else
		{
			path = _getenv("PATH");
			token = _strtok(path, ":");
			while (token != NULL)
			{ _strcpy(command_path, token);
				_strcat(command_path, "/");
				_strcat(command_path, array[0]);
				if (stat(command_path, &st) == 0 && S_ISREG(st.st_mode))
				{
					if (execve(command_path, array, environment) == -1)
					{
						perror("./shell");
						exit(EXIT_FAILURE); }}
				token = _strtok(NULL, ":"); }
			write(STDERR_FILENO, "Command not found: ", 19);
			write(STDERR_FILENO, array[0], _strlen(array[0]));
			write(STDERR_FILENO, "\n", 1);
			exit(EXIT_FAILURE); }}
	else
		waitpid(pid, &status, 0); }
