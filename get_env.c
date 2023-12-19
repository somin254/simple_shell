#include "main.h"

/**
 * _getenv - gets the environment
 * @name: name of the environment
 *
 * Return: environment of the given name
 */

char *_getenv(const char *name)
{
	int i, len = _strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
		{
			return (environ[i] + len + 1);
		}
	}
	return (NULL);
}
