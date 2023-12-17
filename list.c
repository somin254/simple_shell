#include "shell.h"

/**
 * add_node_end - Adds a node to the end of the list
 * @head: The address pointer to the head node
 * @str: The string field of the node
 * @num: The node index used in history
 *
 * Return: A pointer to the new node
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *nodes;

	if (!head)
		return (NULL);

	nodes = *head;
	new_node = malloc(sizeof(list_t));

	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);

		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (nodes)
	{
		while (nodes->next)
			nodes = nodes->next;

		nodes->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * add_node - Adds a node to the start of the list
 * @head: Address of pointer to the head node
 * @str: The string field of the node
 * @num: The node index used in history
 *
 * Return: A pointer to the new node
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);

	new_head = malloc(sizeof(list_t));

	if (!new_head)
		return (NULL);

	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;

	if (str)
	{
		new_head->str = _strdup(str);

		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}

	new_head->next = *head;
	*head = new_head;

	return (new_head);
}

/**
 * delete_node_at_index - Deletes a node at the specified index
 * @head: Address pointer to the first node
 * @index: Index of the node to delete
 *
 * Return: 1 if successful, 0 if failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *head;

	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}

		i++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * free_list - Frees all nodes in the list
 * @head: Address pointer to the head node
 */
void free_list(list_t **head)
{
	list_t *nodes, *next_nodes, *first_node;

	if (!head || !*head)
		return;

	first_node = *head;
	nodes = first_node;

	while (nodes)
	{
		next_nodes = nodes->next;
		free(nodes->str);
		free(nodes);
		nodes = next_nodes;
	}

	*head = NULL;
}

/**
 * print_list_str - Prints only the str element of list_t linked list
 * @head: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t print_list_str(const list_t *head)
{
	size_t size = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		size++;
	}

	return (size);
}
