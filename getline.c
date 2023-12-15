#include "shell.h"

/**
 * input_buffer - Buffers chained commands.
 * @shell_info: Parameter struct.
 * @command_buffer: Address of buffer.
 * @buffer_length: Address of len var.
 *
 * Return: Bytes read.
 */
ssize_t input_buffer(info_t *shell_info, char **command_buffer, size_t *buffer_length)
{
	ssize_t bytes_read = 0;
	size_t buffer_len = 0;

	if (!*buffer_length) /* If nothing left in the buffer, fill it */
	{
		/* bfree((void **)shell_info->cmd_buf); */
		free(*command_buffer);
		*command_buffer = NULL;
		signal(SIGINT, sigint_handler);
#if USE_GETLINE
		bytes_read = getline(command_buffer, &buffer_len, stdin);
#else
		bytes_read = _getline(shell_info, command_buffer, &buffer_len);
#endif
		if (bytes_read > 0)
		{
			if ((*command_buffer)[bytes_read - 1] == '\n')
			{
				(*command_buffer)[bytes_read - 1] = '\0'; /* Remove trailing newline */
				bytes_read--;
			}
			shell_info->linecount_flag = 1;
			remove_comments(*command_buffer);
			build_history_list(shell_info, *command_buffer, shell_info->hist_count++);
			/* if (_strchr(*command_buffer, ';')) Is this a command chain? */
			{
				*buffer_length = bytes_read;
				shell_info->cmd_buffer = command_buffer;
			}
		}
	}
	return (bytes_read);
}

/**
 * get_input - Gets a line minus the newline.
 * @shell_info: Parameter struct.
 *
 * Return: Bytes read.
 */
ssize_t get_input(info_t *shell_info)
{
	static char *command_buf; /* The ';' command chain buffer */
	static size_t i, j, buffer_len;
	ssize_t bytes_read = 0;
	char **command_buf_ptr = &(shell_info->arg), *current_pos;

	_putchar(BUF_FLUSH);
	bytes_read = input_buffer(shell_info, &command_buf, &buffer_len);
	if (bytes_read == -1) /* EOF */
		return (-1);
	if (buffer_len) /* We have commands left in the chain buffer */
	{
		j = i; /* Init new iterator to the current buf position */
		current_pos = command_buf + i; /* Get pointer for return */

		check_chain(shell_info, command_buf, &j, i, buffer_len);
		while (j < buffer_len) /* Iterate to semicolon or end */
		{
			if (is_chain(shell_info, command_buf, &j))
				break;
			j++;
		}

		i = j + 1; /* Increment past nulled ';'' */
		if (i >= buffer_len) /* Reached the end of the buffer? */
		{
			i = buffer_len = 0; /* Reset position and length */
			shell_info->cmd_buf_type = CMD_NORM;
		}

		*command_buf_ptr = current_pos; /* Pass back pointer to the current command position */
		return (_strlen(current_pos)); /* Return the length of the current command */
	}

	*command_buf_ptr = command_buf; /* Else not a chain, pass back buffer from _getline() */
	return (bytes_read); /* Return the length of the buffer from _getline() */
}

/**
 * read_buffer - Reads a buffer.
 * @shell_info: Parameter struct.
 * @buffer: Buffer.
 * @size: Size.
 *
 * Return: Bytes read.
 */
ssize_t read_buffer(info_t *shell_info, char *buffer, size_t *size)
{
	ssize_t bytes_read = 0;

	if (*size)
		return (0);
	bytes_read = read(shell_info->readfd, buffer, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*size = bytes_read;
	return (bytes_read);
}

/**
 * _getline - Gets the next line of input from STDIN.
 * @shell_info: Parameter struct.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: string_length.
 */
int _getline(info_t *shell_info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t bytes_read = 0, string_length = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		string_length = *length;
	if (i == len)
		i = len = 0;

	bytes_read = read_buffer(shell_info, buf, &len);
	if (bytes_read == -1 || (bytes_read == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, string_length, string_length ? string_length + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (string_length)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	string_length += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = string_length;
	*ptr = p;
	return (string_length);
}

/**
 * sigint_handler - Blocks ctrl-C.
 * @sig_num: The signal number.
 *
 * Return: void.
 */
void sigint_handler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
