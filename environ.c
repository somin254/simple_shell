#include "shell.h"

/**
 * _myenv - Print current environment
 * @infos: Struct containing arguments, used to maintain
 * Return: Always 0
 */
int _myenv(info_t *infos)
{
	print_list_str(infos->env);
	return (0);
}

/**
 * _mysetenv - Initialize a new environment variable
 * or modify an existing one
 * @infos: Struct containing arguments, used to maintain
 * Return: Always 0
 */
int _mysetenv(info_t *infos)
{
	if (infos->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	if (_setenv(infos, infos->argv[1], infos->argv[2]))
		return (0);

	return (1);
}

/**
 * _getenv - Gets value of an environment variable
 * @infos: Struct containing arguments, used to maintain
 * @names: Environment variable name
 * Return: Value of the environment variable
 */
char *_getenv(info_t *infos, const char *names)
{
	list_t *node = infos->env;
	char *o;

	while (node)
	{
		o = starts_with(node->str, names);
		if (o && *o)
			return (o);

		node = node->next;
	}

	return (NULL);
}

/**
 * populate_env_list - Populate environment linked list
 * @info: Struct containing arguments, used to maintain
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t z;

	for (z = 0; environ[z]; z++)
		add_node_end(&node, environ[z], 0);

	info->env = node;
	return (0);
}

/**
 * _myunsetenv - Removes the environment variable
 * @infos: Struct containing arguments, used to maintain
 * Return: Always 0
 */
int _myunsetenv(info_t *infos)
{
	int z;

	if (infos->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (z = 1; z <= infos->argc; z++)
		_unsetenv(infos, infos->argv[z]);

	return (0);
}
