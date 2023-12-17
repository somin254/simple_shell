#include "shell.h"
#include <sys/wait.h>  /* Include for waitpid */

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void)
{
    printf("#cisfun$ ");
    fflush(stdout);
}

/**
 * run_shell - Runs the shell.
 */
void run_shell(void)
{
    char buffer[BUFFER_SIZE];
    char *args[2];
    int status;
    pid_t pid;  /* Declare pid at the beginning of the block */

    while (1)
    {
        display_prompt();

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
        {
            printf("\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "exit") == 0)
        {
            break;
        }

        args[0] = buffer;
        args[1] = NULL;

        pid = fork();  /* Move declaration to the beginning */

        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            if (execve(buffer, args, NULL) == -1)
            {
                perror(buffer);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            waitpid(pid, &status, 0);
        }
    }
}

