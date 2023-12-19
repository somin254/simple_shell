#include "shell.h"
/**
 **_strncat - chains two strings
 *@desti: first string
 *@sorc: second string
 *@n: amount of bytes to be max used
 *Return: chained string
 */
char *_strncat(char *desti, char *sorc, int n)
{
int v, k;
char *s = desti;
v = 0;
k = 0;
while (desti[v] != '\0')
v++;
while (sorc[k] != '\0' && k < n)
{
desti[v] = sorc[k];
v++;
k++;
}
if (k < n)
desti[v] = '\0';
return (s);
}
/**
 **_strchr - locates char in string
 *@stri: string to parse
 *@ch: char to look for
 *Return: (s) a pointer to the memory-area s
 */
char *_strchr(char *stri, char ch)
{
do {
if (*stri == ch)
return (stri);
} while (*stri++ != '\0');
return (NULL);
}
/**
 **_strncpy - copies a string
 *@desti: the destination string to be copied to
 *@sorc: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *desti, char *sorc, int n)
{
int v, k;
char *s = desti;
v = 0;
while (sorc[v] != '\0' && v < n - 1)
{
desti[v] = sorc[v];
v++;
}
if (v < n)
{
k = v;
while (k < n)
{
desti[k] = '\0';
k++;
}
}
return (s);
}
