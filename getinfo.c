#include "shell.h"

/**
 * clear_info - Initializes info_t struct.
 * @info: Struct address.
 */
void clear_info(info_t *info)
{
	info->argument = NULL;
	info->argument_vector = NULL;
	info->path = NULL;
	info->argument_count = 0;
}

/**
 * set_info - Initializes info_t struct.
 * @info: Struct address.
 * @arg_vector: Argument vector.
 */
void set_info(info_t *info, char **arg_vector)
{
	int i = 0;

	info->program_name = arg_vector[0];
	if (info->argument)
	{
		info->argument_vector = strtow(info->argument, " \t");
		if (!info->argument_vector)
		{
			info->argument_vector = malloc(sizeof(char *) * 2);
			if (info->argument_vector)
			{
				info->argument_vector[0] = _strdup(info->argument);
				info->argument_vector[1] = NULL;
			}
		}
		for (i = 0; info->argument_vector && info->argument_vector[i]; i++)
			;
		info->argument_count = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Frees info_t struct fields.
 * @info: Struct address.
 * @free_all: True if freeing all fields.
 */
void free_info(info_t *info, int free_all)
{
	ffree(info->argument_vector);
	info->argument_vector = NULL;
	info->path = NULL;
	if (free_all)
	{
		if (!info->command_buffer)
			free(info->argument);
		if (info->environment)
			free_list(&(info->environment));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->command_buffer);
		if (info->read_file_descriptor > 2)
			close(info->read_file_descriptor);
		_putchar(BUF_FLUSH);
	}
}
