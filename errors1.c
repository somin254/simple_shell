#include "shell.h"
/**
 * _erratoi - converts string to int
 * @str: string to convert
 * Return: if no numbers in string (0) converted num
 * otherwise -1 on error
 */
int _erratoi(char *str)
{
int z = 0;
unsigned long int results = 0;
if (*str == '+')
str++;
for (z = 0; str[z] != '\0'; z++)
{
if (str[z] >= '0' && str[z] <= '9')
{
results *= 10;
results += (str[z] - '0');
if (results > INT_MAX)
return (-1);
}
else
return (-1);
}
return (results);
}
/**
 * print_d - prints a decimal int number (base 10)
 * @inputs: input
 * @fd: filedescriptor to write
 *
 * Return: number characters printed
 */
int print_d(int inputs, int fd)
{
int (*__putchar)(char) = _putchar;
int z, counte = 0;
unsigned int _ads_, currents;
if (fd == STDERR_FILENO)
__putchar = _eputchar;
if (inputs < 0)
{
_ads_ = -inputs;
__putchar('-');
counte++;
}
else
_ads_ = inputs;
currents = _ads_;
for (z = 1000000000; z > 1; z /= 10)
{
if (_ads_ / z)
{
__putchar('0' + currents / z);
counte++;
}
currents %= z;
}
__putchar('0' + currents);
counte++;
return (counte);
}
/**
 * print_error - print error msg
 * @infos: parameter and return info struct
 * @est: string with specified type error
 * Return: if no numbers in string 0 converted number
 * otherwise -1 on error
 */
void print_error(info_t *infos, char *est)
{
_eputs(infos->fname);
_eputs(": ");
print_d(infos->line_count, STDERR_FILENO);
_eputs(": ");
_eputs(infos->argv[0]);
_eputs(": ");
_eputs(est);
}
/**
 * remove_comments - replaces '#' with '\0'
 * @buffe: address of string to modify
 *
 * Return: Always (0)
 */
void remove_comments(char *buffe)
{
int z;
for (z = 0; buffe[z] != '\0'; z++)
if (buffe[z] == '#' && (!z || buffe[z - 1] == ' '))
{
buffe[z] = '\0';
break;
}
}
/**
 * convert_number - convert function clone of itoa
 * @numb: number
 * @bases: base
 * @flag: argument flags
 *
 * Return: a string
 */
char *convert_number(long int numb, int bases, int flag)
{
static char *array;
static char buffe[50];
char sign = 0;
char *ptdr;
unsigned long b = numb;
if (!(flag & CONVERT_UNSIGNED) && numb < 0)
{
b = -numb;
sign = '-';
}
array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptdr = &buffe[49];
*ptdr = '\0';
do {
*--ptdr = array[b % bases];
b /= bases;
} while (b != 0);
if (sign)
*--ptdr = sign;
return (ptdr);
}
