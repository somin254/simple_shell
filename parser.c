#include "shell.h"

/**
 * is_cmd - Checks if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	/* Check if path is valid and retrieve file information */
	if (!path || stat(path, &st))
		return (0);

	/* Check if the file is a regular file (executable) */
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Duplicates characters within a specified range.
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to a new buffer.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	/* Copy characters from pathstr to buf within the specified range */
	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - Finds the specified command in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * Return: Full path of cmd if found, or NULL if not found.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	/* Check if pathstr is NULL */
	if (!pathstr)
		return (NULL);

	/* Check if cmd starts with "./" and is an executable */
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	/* Iterate through pathstr to find the command in the PATH directories */
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			/* Duplicate characters within the specified range */
			path = dup_chars(pathstr, curr_pos, i);
			/* Append cmd to the path */
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			/* Check if the full path is an executable command */
			if (is_cmd(info, path))
				return (path);
			/* Break if end of pathstr is reached */
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
