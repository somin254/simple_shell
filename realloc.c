#include "shell.h"

/**
 * _memset - Fills memory with a constant byte
 * @st: Pointer to memory area
 * @bt: Byte to fill *s with
 * @nt: Amount of bytes to fill
 * Return: (st) Pointer to memory area st
 */
char *_memset(char *st, char bt, unsigned int nt)
{
	unsigned int z;

	for (z = 0; z < nt; z++)
		st[z] = bt;

	return (st);
}

/**
 * ffree - Frees a string of strings
 * @ppt: String of strings
 */
void ffree(char **ppt)
{
	char **a = ppt;

	if (!ppt)
		return;

	while (*ppt)
		free(*ppt++);

	free(a);
}

/**
 * _realloc - Reallocates a block of memory
 * @ptdr: Pointer to the previous malloc block
 * @old_sizes: Size of the previous block (bytes)
 * @new_sizes: Size of the new block (bytes)
 * Return: Pointer to the old block nameen.
 */
void *_realloc(void *ptdr, unsigned int old_sizes, unsigned int new_sizes)
{
	char *p;

	if (!ptdr)
		return (malloc(new_sizes));

	if (!new_sizes)
		return (free(ptdr), NULL);

	if (new_sizes == old_sizes)
		return (ptdr);

	p = malloc(new_sizes);

	if (!p)
		return (NULL);

	old_sizes = old_sizes < new_sizes ? old_sizes : new_sizes;

	while (old_sizes--)
		p[old_sizes] = ((char *)ptdr)[old_sizes];

	free(ptdr);

	return (p);
}
