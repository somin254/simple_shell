#include "shell.h"
#include <string.h>

// Print a linked list of strings
void print_list_str(list_t *head) {
    while (head != NULL) {
        printf("%s\n", head->str);
        head = head->next;
    }
}

// Check if a string starts with a given prefix
int starts_with(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

// Add a node to the end of a linked list
void add_node_end(list_t **head, const char *str, int len) {
    list_t *new_node = malloc(sizeof(list_t));
    if (new_node == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    new_node->str = malloc(len + 1);
    if (new_node->str == NULL) {
        perror("malloc");
        free(new_node);
        exit(EXIT_FAILURE);
    }

    strcpy(new_node->str, str);
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        list_t *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Set an environment variable
int _setenv(info_t *infos, const char *name, const char *value) {
    char *env_var;
    size_t len;

    // Construct the environment variable string
    len = strlen(name) + 1 + strlen(value) + 1;
    env_var = malloc(len);
    if (env_var == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    snprintf(env_var, len, "%s=%s", name, value);

    // Add the environment variable to the list
    add_node_end(&(infos->env_list), env_var, len);

    // Also set the environment variable in the array (for execve)
    _setenv_array(infos, name, value);

    free(env_var);
    return 0;
}

// Unset an environment variable
void _unsetenv(info_t *infos, const char *name) {
    // Remove the environment variable from the list
    list_t **current = &(infos->env_list);
    while (*current != NULL) {
        if (starts_with((*current)->str, name)) {
            list_t *temp = *current;
            *current = (*current)->next;
            free(temp->str);
            free(temp);
            break;
        }
        current = &((*current)->next);
    }

    // Also unset the environment variable in the array (for execve)
    _unsetenv_array(infos, name);
}
