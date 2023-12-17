#include "shell.h"
/**
 * get_history_file - get history file
 * @infos: param struct
 *
 * Return: allocated string with history file
 */
char *get_history_file(info_t *infos)
{
char *buff, *dirt;
dirt = _getenv(infos, "HOME=");
if (!dirt)
return (NULL);
buff = malloc(sizeof(char) * (_strlen(dirt) + _strlen(HIST_FILE) + 2));
if (!buff)
return (NULL);
buff[0] = 0;
_strcpy(buff, dirt);
_strcat(buff, "/");
_strcat(buff, HIST_FILE);
return (buff);
}
/**
 * write_history - creates a file/appends to existing file
 * @infos: param struct
 *
 * Return: if success 1 else -1
 */
int write_history(info_t *infos)
{
ssize_t fd;
list_t *nodes = NULL;
char *filenam = get_history_file(infos);
if (!filenam)
return (-1);
fd = open(filenam, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filenam);
if (fd == -1)
return (-1);
for (nodes = infos->history; nodes; nodes = nodes->next)
{
_putsfd(nodes->str, fd);
_putfd('\n', fd);
}
_putfd(BUF_FLUSH, fd);
close(fd);
return (1);
}
/**
 * read_history - read history of file
 * @infos: param struct
 *
 * Return: if success hist-count otherwise 0
 */
int read_history(info_t *infos)
{
ssize_t fd, rdlen, fsize = 0;
int i, lasts = 0, linecounts = 0;
struct stat st;
char *buff = NULL, *filename = get_history_file(infos);
if (!filename)
return (0);
fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buff = malloc(sizeof(char) * (fsize + 1));
if (!buff)
return (0);
rdlen = read(fd, buff, fsize);
buff[fsize] = 0;
if (rdlen <= 0)
return (free(buff), 0);
close(fd);
for (i = 0; i < fsize; i++)
if (buff[i] == '\n')
{
buff[i] = 0;
build_history_list(infos, buff + lasts, linecounts++);
lasts = i + 1;
}
if (lasts != i)
build_history_list(infos, buff + lasts, linecounts++);
free(buff);
infos->histcount = linecounts;
while (infos->histcount-- >= HIST_MAX)
delete_node_at_index(&(infos->history), 0);
renumber_history(infos);
return (infos->histcount);
}
/**
 * renumber_history - after change, renumbers histo linked list
 * @infos: Struct containing arguments, used to maintain.
 *
 * Return: new histcount
 */
int renumber_history(info_t *infos)
{
list_t *node = infos->history;
int z = 0;
while (node)
{
node->num = z++;
node = node->next;
}
return (infos->histcount = z);
}
/**
 * build_history_list - add entry to hist linked list
 * @infos: Struct containing arguments, used to maintain.
 * @buff: buffer
 * @linecounts: history linecount (histcount)
 *
 * Return: Always (0)
 */
int build_history_list(info_t *infos, char *buff, int linecounts)
{
list_t *node = NULL;
if (infos->history)
node = infos->history;
add_node_end(&node, buff, linecounts);
if (!infos->history)
infos->history = node;
return (0);
}
