#include "shell.h"

/**
 * bfree - Deallocates memory associated with a pointer and sets it to NULL.
 * @ptr: Address of the pointer to be freed.
 *
 * Return: 1 if memory is freed, otherwise 0.
 */
int bfree(void **ptr)
{
	/* Check if the pointer is not NULL and the content is not NULL */
	if (ptr && *ptr)
	{
		/* Free the allocated memory */
		free(*ptr);
		/* Set the pointer to NULL to avoid dangling references */
		*ptr = NULL;
		/* Memory successfully freed */
		return (1);
	}
	/* Pointer or content was already NULL, no action taken */
	return (0);
}
