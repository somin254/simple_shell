#include "shell.h"
#include <unistd.h>

/**
 * _putfd - Writes char to the given file descriptor.
 * @ch: Char to print.
 * @fd: File descriptor to write.
 *
 * Return: 1 if success. -1 if error, and errno is set appropriately.
 */
int _putfd(char ch, int fd)
{
    static int index;
    static char buffer[WRITE_BUF_SIZE];

    if (ch == BUF_FLUSH || index >= WRITE_BUF_SIZE)
    {
        write(fd, buffer, index);
        index = 0;
    }

    if (ch != BUF_FLUSH)
        buffer[index++] = ch;

    return (1);
}

/**
 * _eputchar - Writes char to stderr.
 * @ch: Char to print.
 *
 * Return: 1 if success. -1 if error, and errno is set appropriately.
 */
int _eputchar(char ch)
{
    static int index;
    static char buffer[WRITE_BUF_SIZE];

    if (ch == BUF_FLUSH || index >= WRITE_BUF_SIZE)
    {
        write(2, buffer, index);
        index = 0;
    }

    if (ch != BUF_FLUSH)
        buffer[index++] = ch;

    return (1);
}
