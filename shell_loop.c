#include "shell.h"
/**
 * hsh - main shell (loop)
 * @infos: param & return info struct
 * @avc: argument vector from main()
 *
 * Return: if success 0, if error 1 or error code
 */
int hsh(info_t *infos, char **avc)
{
ssize_t r = 0;
int builtin_ret = 0;
while (r != -1 && builtin_ret != -2)
{
clear_info(infos);
if (interactive(infos))
_puts("$ ");
_eputchar(BUF_FLUSH);
r = get_input(infos);
if (r != -1)
{
set_info(infos, avc);
builtin_ret = find_builtin(infos);
if (builtin_ret == -1)
find_cmd(infos);
}
else if (interactive(infos))
_putchar('\n');
free_info(infos, 0);
}
write_history(infos);
free_info(infos, 1);
if (!interactive(infos) && infos->status)
exit(infos->status);
if (builtin_ret == -2)
{
if (infos->err_num == -1)
exit(infos->status);
exit(infos->err_num);
}
return (builtin_ret);
}
/**
 * find_builtin - finds builtin cmd
 * @infos: param / return info struct
 *
 * Return: if builtin not found -1,
 * 	if builtin executed success 0,
 * 	if builtin found but not success 1,
 * 	if builtin signals exit() 2
 */
int find_builtin(info_t *infos)
{
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", _myexit},
{"env", _myenv},
{"help", _myhelp},
{"history", _myhistory},
{"setenv", _mysetenv},
{"unsetenv", _myunsetenv},
{"cd", _mycd},
{"alias", _myalias},
{NULL, NULL}};
for (i = 0; builtintbl[i].type; i++)
if (_strcmp(infos->argv[0], builtintbl[i].type) == 0)
{
infos->line_count++;
built_in_ret = builtintbl[i].func(infos);
break;
}
return (built_in_ret);
}
/**
 * find_cmd - finds cmd in path
 * @infos: param & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *infos)
{
char *path = NULL;
int i, kc;
infos->path = infos->argv[0];
if (infos->linecount_flag == 1)
{
infos->line_count++;
infos->linecount_flag = 0;
}
for (i = 0, kc = 0; infos->arg[i]; i++)
if (!is_delim(infos->arg[i], " \t\n"))
kc++;
if (!kc)
return;
path = find_path(infos, _getenv(infos, "PATH="), infos->argv[0]);
if (path)
{
infos->path = path;
fork_cmd(infos);
}
else
{
if ((interactive(infos) || _getenv(infos, "PATH=") || infos->argv[0][0] == '/') && is_cmd(infos, infos->argv[0]))
fork_cmd(infos);
else if (*(infos->arg) != '\n')
{
infos->status = 127;
print_error(infos, "not found\n");
}
}
}
/**
 * fork_cmd - forks an exec thread to run cmd
 * @infos: param & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *infos)
{
pid_t child_pid;
child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(infos->path, infos->argv, get_environ(infos)) == -1)
{
free_info(infos, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(infos->status));
if (WIFEXITED(infos->status))
{
infos->status = WEXITSTATUS(infos->status);
if (infos->status == 126)
print_error(infos, "Permission denied\n");
}
}
}
