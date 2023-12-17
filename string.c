#include "shell.h"
/**
 * _strlen - return length of string
 * @st: string whose length to check
 *
 * Return: int length of string
 */
int _strlen(char *st)
{
int i = 0;
if (!st)
return (0);
while (*st++)
i++;
return (i);
}
/**
 * starts_with - check if needle start with haystack
 * @haystacks: string to find
 * @needles: substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystacks, const char *needles)
{
while (*needles)
if (*needles++ != *haystacks++)
return (NULL);
return ((char *)haystacks);
}
/**
 * _strcat - chains two strings
 * @desti: destination buffer
 * @sorc: source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *desti, char *sorc)
{
char *ret = desti;
while (*desti)
desti++;
while (*sorc)
*desti++ = *sorc++;
*desti = *sorc;
return (ret);
}
/**
 * _strcmp - performs comp of two strings.
 * @str1: first strang
 * @str2: second strang
 *
 * Return: if str1 < str2 -,if str1 > str2 +, if str1 == str2 0
 */
int _strcmp(char *str1, char *str2)
{
while (*str1 && *str2)
{
if (*str1 != *str2)
return (*str1 - *str2);
str1++;
str2++;
}
if (*str1 == *str2)
return (0);
else
return (*str1 < *str2 ? -1 : 1);
}
