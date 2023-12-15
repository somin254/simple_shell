#include "shell.h"

/**
 * get_environ - Returns the string array copy of our environ.
 * @shell_info: Structure containing potential arguments.
 * Return: Always 0.
 */
char **get_environ(info_t *shell_info)
{
	if (!shell_info->environ || shell_info->env_changed)
	{
		shell_info->environ = list_to_strings(shell_info->env);
		shell_info->env_changed = 0;
	}

	return (shell_info->environ);
}

/**
 * _unsetenv - Removes an environment variable.
 * @shell_info: Structure containing potential arguments.
 * Return: 1 on delete, 0 otherwise.
 * @var_name: The string env var property.
 */
int _unsetenv(info_t *shell_info, char *var_name)
{
	list_t *node = shell_info->env;
	size_t index = 0;
	char *position;

	if (!node || !var_name)
		return (0);

	while (node)
	{
		position = starts_with(node->str, var_name);
		if (position && *position == '=')
		{
			shell_info->env_changed = delete_node_at_index(&(shell_info->env), index);
			index = 0;
			node = shell_info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (shell_info->env_changed);
}

/**
 * _setenv - Initializes a new environment variable,
 *            or modifies an existing one.
 * @shell_info: Structure containing potential arguments.
 * @var_name: The string env var property.
 * @var_value: The string env var value.
 * Return: Always 0.
 */
int _setenv(info_t *shell_info, char *var_name, char *var_value)
{
	char *buffer = NULL;
	list_t *node;
	char *position;

	if (!var_name || !var_value)
		return (0);

	buffer = malloc(_strlen(var_name) + _strlen(var_value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var_name);
	_strcat(buffer, "=");
	_strcat(buffer, var_value);
	node = shell_info->env;
	while (node)
	{
		position = starts_with(node->str, var_name);
		if (position && *position == '=')
		{
			free(node->str);
			node->str = buffer;
			shell_info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(shell_info->env), buffer, 0);
	free(buffer);
	shell_info->env_changed = 1;
	return (0);
}
