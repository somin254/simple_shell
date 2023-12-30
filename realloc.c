#include "shell.h"

/**
 **_memset - Fills memory with a constant byte.
 *@s: Pointer to the memory area.
 *@b: The byte to fill *s with.
 *@n: The number of bytes to be filled.
 *Return: (s) a pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	/* Fill memory with the specified byte */
	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - Frees a string of strings.
 * @pp: String of strings.
 */
void ffree(char **pp)
{
	char **a = pp;

	/* Check if pp is not NULL and free each string in the array */
	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	/* Free the array of strings */
	free(a);
}

/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * Return: Pointer old block if realloc fails,
 * else a pointer to the new block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	/* If ptr is NULL, allocate a new block of size new_size */
	if (!ptr)
		return (malloc(new_size));
	/* If new_size is 0, free the old block and return NULL */
	if (!new_size)
		return (free(ptr), NULL);
	/* If old_size is equal to new_size, no need to reallocate */
	if (new_size == old_size)
		return (ptr);

	/* Allocate a new block of size new_size */
	p = malloc(new_size);
	if (!p)
		return (NULL);

	/* Copy the content of the old block to the new block */
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	/* Free the old block */
	free(ptr);
	return (p);
}
