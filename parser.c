#include "shell.h"
/**
 * is_cmd - determine if file is an exec cmd
 * @infos: info struct
 * @paths: path to file
 *
 * Return: if true 1 otherwise 0
 */
int is_cmd(info_t *infos, char *paths)
{
struct stat st;
(void)infos;
if (!paths || stat(paths, &st))
return (0);
if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}
/**
 * dup_chars - duplicates chars
 * @pathstrg: PATH string
 * @star: start id
 * @sto: stop id
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstrg, int star, int sto)
{
static char buff[1024];
int i = 0, k = 0;
for (k = 0, i = star; i < sto; i++)
if (pathstrg[i] != ':')
buff[k++] = pathstrg[i];
buff[k] = 0;
return (buff);
}
/**
 * find_path - finds cmd in PATH string
 * @infos: info struct
 * @pathstri: PATH string
 * @cmd: cmd to find
 *
 * Return: path of cmd if found else NULL
 */
char *find_path(info_t *infos, char *pathstri, char *cmd)
{
int z = 0, curr_pos = 0;
char *path;
if (!pathstri)
return (NULL);
if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_cmd(infos, cmd))
return (cmd);
}
while (1)
{
if (!pathstri[z] || pathstri[z] == ':')
{
path = dup_chars(pathstri, curr_pos, z);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (is_cmd(infos, path))
return (path);
if (!pathstri[z])
break;
curr_pos = z;
}
z++;
}
return (NULL);
}
