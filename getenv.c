#include "shell.h"

/**
 * _unsetenv - Remove an environment variable
 * @infos: Struct containing arguments, used to maintain.
 *         const func prototype.
 * @vari: string env var property
 * Return: 1 if delete, 0 otherwise
 */
int _unsetenv(info_t *infos, char *vari)
{
	list_t *node = infos->env;
	size_t v = 0;
	char *p;

	if (!node || !vari)
		return (0);

	while (node)
	{
		p = starts_with(node->str, vari);
		if (p && *p == '=')
		{
			infos->env_changed = delete_node_at_index(&(infos->env), v);
			v = 0;
			node = infos->env;
			continue;
		}
		node = node->next;
		v++;
	}

	return (infos->env_changed);
}

/**
 * _setenv - Initialize new env var, or modify existing one
 * @infos: Struct containing arguments, used to maintain.
 *         const func prototype.
 * @vari: string env var prop
 * @values: string env var val
 * Return: 0 on success, 1 on failure
 */
int _setenv(info_t *infos, char *vari, char *values)
{
	char *buff = NULL;
	list_t *node;
	char *p;

	if (!vari || !values)
		return (0);

	buff = malloc(_strlen(vari) + _strlen(values) + 2);
	if (!buff)
		return (1);

	_strcpy(buff, vari);
	_strcat(buff, "=");
	_strcat(buff, values);

	node = infos->env;
	while (node)
	{
		p = starts_with(node->str, vari);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buff;
			infos->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

	add_node_end(&(infos->env), buff, 0);
	free(buff);
	infos->env_changed = 1;
	return (0);
}

/**
 * get_environ - gets value of environ variable
 * @infos: Struct containing arguments, used to maintain.
 *         const func prototype.
 * Return: Always (0)
 */
char **get_environ(info_t *infos)
{
	if (!infos->environ || infos->env_changed)
	{
		infos->environ = list_to_strings(infos->env);
		infos->env_changed = 0;
	}

	return (infos->environ);
}

