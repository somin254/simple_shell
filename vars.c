#include "shell.h"
/**
 * is_chain - test current char in buffer if is a chain delimeter
 * @infos: parameter struct
 * @buff: char buffer
 * @po: address of current posi in buf
 *
 * Return: if chain delimeter 1 otherwise 0
 */
int is_chain(info_t *infos, char *buff, size_t *po)
{
size_t j = *po;
if (buff[j] == '|' && buff[j + 1] == '|')
{
buff[j] = 0;
j++;
infos->cmd_buf_type = CMD_OR;
}
else if (buff[j] == '&' && buff[j + 1] == '&')
{
buff[j] = 0;
j++;
infos->cmd_buf_type = CMD_AND;
}
else if (buff[j] == ';')
{
buff[j] = 0;
infos->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*po = j;
return (1);
}
/**
 * check_chain - checks if should continue chaining based on last stat
 * @infos: param struct
 * @buff: char buffer
 * @po: address current position in buf
 * @id: starting position in buf
 * @leng: length buf
 *
 * Return: Void
 */
void check_chain(info_t *infos, char *buff, size_t *po, size_t id, size_t leng)
{
size_t j = *po;
if (infos->cmd_buf_type == CMD_AND)
{
if (infos->status)
{
buff[id] = 0;
j = leng;
}
}
if (infos->cmd_buf_type == CMD_OR)
{
if (!infos->status)
{
buff[id] = 0;
j = leng;
}
}
*po = j;
}
/**
 * replace_alias - replaces aliases in tokenized string
 * @infos: param struct
 *
 * Return: if replaced 1, 0 otherwise
 */
int replace_alias(info_t *infos)
{
int i;
list_t *nodes;
char *p;
for (i = 0; i < 10; i++)
{
nodes = node_starts_with(infos->alias, infos->argv[0], '=');
if (!nodes)
return (0);
free(infos->argv[0]);
p = _strchr(nodes->str, '=');
if (!p)
return (0);
p = _strdup(p + 1);
if (!p)
return (0);
infos->argv[0] = p;
}
return (1);
}
/**
 * replace_vars - replaces vars in token string
 * @infos: param struct
 *
 * Return: if replaced 1, 0 otherwise
 */
int replace_vars(info_t *infos)
{
int i = 0;
list_t *node;
for (i = 0; infos->argv[i]; i++)
{
if (infos->argv[i][0] != '$' || !infos->argv[i][1])
continue;
if (!_strcmp(infos->argv[i], "$?"))
{
replace_string(&(infos->argv[i]),
_strdup(convert_number(infos->status, 10, 0)));
continue;
}
if (!_strcmp(infos->argv[i], "$$"))
{
replace_string(&(infos->argv[i]),
_strdup(convert_number(getpid(), 10, 0)));
continue;
}
node = node_starts_with(infos->env, &infos->argv[i][1], '=');
if (node)
{
replace_string(&(infos->argv[i]),
_strdup(_strchr(node->str, '=') + 1));
continue;
}
replace_string(&infos->argv[i], _strdup(""));
}
return (0);
}
/**
 * replace_string - replace string
 * @olds: address olds string
 * @news: news string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **olds, char *news)
{
free(*olds);
*olds = news;
return (1);
}
