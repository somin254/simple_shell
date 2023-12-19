#include "main.h"

/**
 * execute - shifts the process to execute another program
 * @cmd_array: list of commands passed to the prompt
 * @environment: used in implementing clear command
 *
 * Return: Nothing
 */

void execute(char *cmd_array[], char *const *environment)
{
    int process_status;
    char *path, *token, cmd_path[1024];
    struct stat file_stat;
    pid_t process_id = fork();

    if (process_id == -1)
    {
        perror("Fork Failed!");
        exit(EXIT_FAILURE);
    }
    else if (process_id == 0)
    {
        if (cmd_array[0][0] == '/' || cmd_array[0][0] == '.')
        {
            if (stat(cmd_array[0], &file_stat) == 0 && S_ISREG(file_stat.st_mode))
            {
                if (execve(cmd_array[0], cmd_array, environment) == -1)
                {
                    perror("./shell");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else
        {
            path = _getenv("PATH");
            token = _strtok(path, ":");
            while (token != NULL)
            {
                _strcpy(cmd_path, token);
                _strcat(cmd_path, "/");
                _strcat(cmd_path, cmd_array[0]);
                if (stat(cmd_path, &file_stat) == 0 && S_ISREG(file_stat.st_mode))
                {
                    if (execve(cmd_path, cmd_array, environment) == -1)
                    {
                        perror("./shell");
                        exit(EXIT_FAILURE);
                    }
                }
                token = _strtok(NULL, ":");
            }
            write(STDERR_FILENO, "Command not found: ", 19);
            write(STDERR_FILENO, cmd_array[0], _strlen(cmd_array[0]));
            write(STDERR_FILENO, "\n", 1);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(process_id, &process_status, 0);
    }
}

