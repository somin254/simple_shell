#include "shell.h"
/**
 * add_node_end - add node to end of list
 * @headz: the address pointer to head node
 * @str: stri field node
 * @num: node index used in history
 *
 * Return: size list
 */
list_t *add_node_end(list_t **headz, const char *str, int num)
{
list_t *new_nodes, *nodes;
if (!headz)
return (NULL);
nodes = *headz;
new_nodes = malloc(sizeof(list_t));
if (!new_nodes)
return (NULL);
_memset((void *)new_nodes, 0, sizeof(list_t));
new_nodes->num = num;
if (str)
{
new_nodes->str = _strdup(str);
if (!new_nodes->str)
{
free(new_nodes);
return (NULL);
}
}
if (nodes)
{
while (nodes->next)
nodes = nodes->next;
nodes->next = new_nodes;
}
else
*headz = new_nodes;
return (new_nodes);
}
/**
 * add_node - adds a node to the start of the list
 * @headz: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **headz, const char *str, int num)
{
list_t *new_headz;
if (!headz)
return (NULL);
new_headz = malloc(sizeof(list_t));
if (!new_headz)
return (NULL);
_memset((void *)new_headz, 0, sizeof(list_t));
new_headz->num = num;
if (str)
{
new_headz->str = _strdup(str);
if (!new_headz->str)
{
free(new_headz);
return (NULL);
}
}
new_headz->next = *headz;
*headz = new_headz;
return (new_headz);
}
/**
 * delete_node_at_index - delete node at index
 * @headz: address pointer first node
 * @id: id of node to delete
 *
 * Return: if success 1 if failure 0
 */
int delete_node_at_index(list_t **headz, unsigned int id)
{
list_t *node, *previo_node;
unsigned int i = 0;
if (!headz || !*headz)
return (0);
if (!id)
{
node = *headz;
*headz = (*headz)->next;
free(node->str);
free(node);
return (1);
}
node = *headz;
while (node)
{
if (i == id)
{
previo_node->next = node->next;
free(node->str);
free(node);
return (1);
}
i++;
previo_node = node;
node = node->next;
}
return (0);
}
/**
 * free_list - free all nodes
 * @head_ptdr: address pointer head node
 *
 * Return: void
 */
void free_list(list_t **head_ptdr)
{
list_t *nodes, *next_nodes, *head;
if (!head_ptdr || !*head_ptdr)
return;
head = *head_ptdr;
nodes = head;
while (nodes)
{
next_nodes = nodes->next;
free(nodes->str);
free(nodes);
nodes = next_nodes;
}
*head_ptdr = NULL;
}
/**
 * print_list_str - print only str element of list_t linked
 * @hp: point first node
 *
 * Return: size list
 */
size_t print_list_str(const list_t *hp)
{
size_t z = 0;
while (hp)
{
_puts(hp->str ? hp->str : "(nil)");
_puts("\n");
hp = hp->next;
z++;
}
return (z);
}
