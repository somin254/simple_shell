#include "shell.h"

/**
 * list_len - Finds the length of the linked list
 * @hp: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t list_len(const list_t *hp)
{
	size_t z = 0;

	while (hp)
	{
		hp = hp->next;
		z++;
	}
	return (z);
}

/**
 * list_to_strings - Returns an array of strings from the list
 * @heads: Pointer to the first node
 *
 * Return: Array of strings
 */
char **list_to_strings(list_t *heads)
{
	list_t *nodes = heads;
	size_t i = list_len(heads), v;
	char **strt;
	char *str;

	if (!heads || !i)
		return (NULL);

	strt = malloc(sizeof(char *) * (i + 1));
	if (!strt)
		return (NULL);

	for (i = 0; nodes; nodes = nodes->next, i++)
	{
		str = malloc(_strlen(nodes->str) + 1);
		if (!str)
		{
			for (v = 0; v < i; v++)
				free(strt[v]);
			free(strt);
			return (NULL);
		}
		str = _strcpy(str, nodes->str);
		strt[i] = str;
	}
	strt[i] = NULL;
	return (strt);
}

/**
 * print_list - Print components of list_t linked list
 * @hp: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t print_list(const list_t *hp)
{
	size_t z = 0;

	while (hp)
	{
		_puts(convert_number(hp->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hp->str ? hp->str : "(nil)");
		_puts("\n");
		hp = hp->next;
		z++;
	}
	return (z);
}

/**
 * node_starts_with - Returns the node where the string starts with a prefix
 * @nodes: Pointer to the list-head
 * @prefix: The string to match
 * @ch: Next char after prefix to match
 *
 * Return: Matched node or NULL
 */
list_t *node_starts_with(list_t *nodes, char *prefix, char ch)
{
	char *p = NULL;

	while (nodes)
	{
		p = starts_with(nodes->str, prefix);
		if (p && ((ch == -1) || (*p == ch)))
			return (nodes);
		nodes = nodes->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets the index of a node
 * @heads: Pointer to the list head
 * @nodes: Pointer to the node
 *
 * Return: Index of the node or -1
 */
ssize_t get_node_index(list_t *heads, list_t *nodes)
{
	size_t i = 0;

	while (heads)
	{
		if (heads == nodes)
			return (i);
		heads = heads->next;
		i++;
	}
	return (-1);
}
