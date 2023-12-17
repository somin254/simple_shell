#include "shell.h"
/**
* bfree - free pointer and NULLs address
* @ptdr: address of pointer to free
*
* Return: if freed 1 otherwise 0.
*/
int bfree(void **ptdr)
{
if (ptdr && *ptdr)
{
free(*ptdr);
*ptdr = NULL;
return (1);
}
return (0);
}
