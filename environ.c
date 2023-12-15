#include "shell.h"
#include <stdint.h>

/**
 * printCurrentEnvironment - Prints the current environment.
 * @infos: Struct containing arguments, used to maintain const func prototype.
 *
 * Return: Always 0.
 */
int printCurrentEnvironment(info_t *infos)
{
    print_list_str((list_t *)infos->env);
    return 0;
}

/**
 * getEnvVarValue - Gets the value of an environment variable.
 * @infos: Struct containing arguments, used to maintain.
 * @names: Environment variable name.
 *
 * Return: Value of the environment variable.
 */
char *getEnvVarValue(info_t *infos, const char *names)
{
    list_t *currentNode = (list_t *)infos->env;
    char *position = NULL;

    while (currentNode)
    {
        uintptr_t result = starts_with(currentNode->str, names);
        if (result && *(char *)result)
        {
            position = (char *)(uintptr_t)result;
            break; /* Exit the loop if a match is found */
        }
        currentNode = currentNode->next;
    }

    return position;
}

/**
 * populateEnvList - Populates the environment linked list.
 * @info: Struct containing arguments, used to maintain const func prototype.
 *
 * Return: Always 0.
 */
int populateEnvList(info_t *info)
{
    list_t *node = NULL;
    size_t index;

    extern char **environ; /* Declare extern to use the global variable */

    for (index = 0; environ[index]; index++)
        add_node_end(&node, environ[index], 0);

    info->env = (void *)node;
    return 0;
}

/**
 * removeEnvVar - Removes an environment variable.
 * @infos: Struct containing arguments, used to maintain const func prototype.
 *
 * Return: Always 0.
 */
int removeEnvVar(info_t *infos)
{
    int index;

    if (infos->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return 1;
    }

    for (index = 1; index < infos->argc; index++)
        _unsetenv(infos, infos->argv[index]);

    return 0;
}

