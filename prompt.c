#include "main.h"

/**
 * _isatty - Determines whether or not to print "$ "
 * @f_descriptor: File descriptor
 *
 * Return: Returns an integer (boolean-like integer, where 0 usually means
 * false and any non-zero value means true).
 */
int _isatty(int f_descriptor)
{
	struct stat buf;

	return (fstat(f_descriptor, &buf) == 0 && S_ISCHR(buf.st_mode));
}

/**
 * prompt - Displays "$ " and waits for the user to type a command
 *
 * Return: Nothing
 */
int prompt(void)
{
	if ((_isatty(STDIN_FILENO) == 1) && (_isatty(STDOUT_FILENO) == 1))
	{
		write(STDERR_FILENO, "$ ", 2);
		return (-1);
	}
	else
	{
		return (0);
	}
}
