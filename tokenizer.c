#include "shell.h"
/**
 * **strtow - split string into words (Repeat delims are ignored)
 * @stri: input string
 * @dc: delimeter string
 * Return: pointer to an array strings, or NULL on failure
 */
char **strtow(char *stri, char *dc)
{
int i, c, kc, m, numword = 0;
char **s;
if (stri == NULL || stri[0] == 0)
return (NULL);
if (!dc)
dc = " ";
for (i = 0; stri[i] != '\0'; i++)
if (!is_delim(stri[i], dc) && (is_delim(stri[i + 1], dc) || !stri[i + 1]))
numword++;
if (numword == 0)
return (NULL);
s = malloc((1 + numword) *sizeof(char *));
if (!s)
return (NULL);
for (i = 0, c = 0; c < numword; c++)
{
while (is_delim(stri[i], dc))
i++;
kc = 0;
while (!is_delim(stri[i + kc], dc) && stri[i + kc])
kc++;
s[c] = malloc((kc + 1) * sizeof(char));
if (!s[c])
{
for (kc = 0; kc < c; kc++)
free(s[kc]);
free(s);
return (NULL);
}
for (m = 0; m < kc; m++)
s[c][m] = stri[i++];
s[c][m] = 0;
}
s[c] = NULL;
return (s);
}
/**
 * **strtow2 - split string into words
 * @stri: input string
 * @dc: delimeter
 * Return: pointer to array of strings or NULL on failure
 */
char **strtow2(char *stri, char dc)
{
int i, c, kc, m, numword = 0;
char **s;
if (stri == NULL || stri[0] == 0)
return (NULL);
for (i = 0; stri[i] != '\0'; i++)
if ((stri[i] != dc && stri[i + 1] == dc) ||
(stri[i] != dc && !stri[i + 1]) || stri[i + 1] == dc)
numword++;
if (numword == 0)
return (NULL);
s = malloc((1 + numword) *sizeof(char *));
if (!s)
return (NULL);
for (i = 0, c = 0; c < numword; c++)
{
while (stri[i] == dc && stri[i] != dc)
i++;
kc = 0;
while (stri[i + kc] != dc && stri[i + kc] && stri[i + kc] != dc)
kc++;
s[c] = malloc((kc + 1) * sizeof(char));
if (!s[c])
{
for (kc = 0; kc < c; kc++)
free(s[kc]);
free(s);
return (NULL);
}
for (m = 0; m < kc; m++)
s[c][m] = stri[i++];
s[c][m] = 0;
}
s[c] = NULL;
return (s);
}
