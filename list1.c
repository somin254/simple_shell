#include "shell.h"

/**
 * list_len - determines length of linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t list_len(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *current = head;
	size_t size = list_len(head), index;
	char **str_array;
	char *str;

	if (!head || !size)
		return (NULL);

	str_array = malloc(sizeof(char *) * (size + 1));
	if (!str_array)
		return (NULL);

	for (index = 0; current; current = current->next, index++)
	{
		str = malloc(_strlen(current->str) + 1);
		if (!str)
		{
			for (size_t j = 0; j < index; j++)
				free(str_array[j]);
			free(str_array);
			return (NULL);
		}

		str = _strcpy(str, current->str);
		str_array[index] = str;
	}
	str_array[index] = NULL;
	return (str_array);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_list(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @head: pointer to the list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or NULL
 */
list_t *node_starts_with(list_t *head, char *prefix, char c)
{
	char *p = NULL;

	while (head)
	{
		p = starts_with(head->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to the list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
