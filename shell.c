#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define UNUSED(x) (void)(x)

int _setenv(info_t *infos, const char *name, const char *value) {
    UNUSED(infos);
    UNUSED(name);
    UNUSED(value);
    /* Implementation of _setenv */
    return 0;
}

void _setenv_array(info_t *infos, const char *name, const char *value) {
    UNUSED(infos);
    UNUSED(name);
    UNUSED(value);
    /* Implementation of _setenv_array */
}

void _unsetenv_array(info_t *infos, const char *name) {
    UNUSED(infos);
    UNUSED(name);
    /* Implementation of _unsetenv_array */
}

int main(void) {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("%s", PROMPT);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove the trailing newline character
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) {
            break;
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execlp(command, command, NULL) == -1) {
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                fprintf(stderr, "./shell: %s: command not found\n", command);
            }
        }
    }

    return 0;
}

