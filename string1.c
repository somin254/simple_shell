#include "shell.h"
/**
 * _strcpy - copie string
 * @desti: destination
 * @sorc: source
 *
 * Return: pointer to dest
 */
char *_strcpy(char *desti, char *sorc)
{
int z = 0;
if (desti == sorc || sorc == 0)
return (desti);
while (sorc[z])
{
desti[z] = sorc[z];
z++;
}
desti[z] = 0;
return (desti);
}
/**
 * _strdup - duplicate string
 * @st: string to duplicate
 *
 * Return: pointer to duplicate string
 */
char *_strdup(const char *st)
{
int lengths = 0;
char *ret;
if (st == NULL)
return (NULL);
while (*st++)
lengths++;
ret = malloc(sizeof(char) * (lengths + 1));
if (!ret)
return (NULL);
for (lengths++; lengths--;)
ret[lengths] = *--st;
return (ret);
}
/**
 * _puts - print input string
 * @st: string to print
 *
 * Return: Nothing
 */
void _puts(char *st)
{
int i = 0;
if (!st)
return;
while (st[i] != '\0')
{
_putchar(st[i]);
i++;
}
}
/**
 * _putchar - writes charc to stdout
 * @ch: char to print
 *
 * Return: if success 1.
 * if error -1 is returned, and errno is set appropriately.
 */
int _putchar(char ch)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buf, i);
i = 0;
}
if (ch != BUF_FLUSH)
buf[i++] = ch;
return (1);
}
