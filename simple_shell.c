#include "shell.h"

void display_prompt(void) {
    printf("#cisfun$ ");
}

void execute_command(char *command) {
    pid_t child_pid;
    int status;

    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        /* Child process */
        if (execlp(command, command, (char *)NULL) == -1) {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    } else {
        /* Parent process */
        waitpid(child_pid, &status, 0);
    }
}

int main(void) {
    char buffer[BUFFER_SIZE];

    while (1) {
        display_prompt();

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            printf("\n");
            break;  // End of file (Ctrl+D) condition
        }

        // Remove the trailing newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "exit") == 0) {
            printf("Exiting shell.\n");
            break;
        }

        execute_command(buffer);
    }

    return EXIT_SUCCESS;
}
