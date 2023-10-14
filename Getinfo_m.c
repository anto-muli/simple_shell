#include "shell.h"
/**
 * clear_info - This function, initializes an info_t struct.
 * @info: The address of the struct to be initialized.
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - This function, initializes an info_t struct.
 * @info: The address of the struct to be initialized
 * @av: The argument vector to populate the struct.
 */
void set_info(info_t *info, char **av)
{
	int x = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (x = 0; info->argv && info->argv[x]; x++)
			;
		info->argc = x;
		replace_alias(info);
		replace_vars(info);
	}
}


/**
 * free_info - releases memory associated with fields of the info_t struct.
 * @info: The address of the struct whose fields are to be freed.
 * @all: A boolean indicating whether to free all fields (true)
 * or a subset (false).
 */
void free_info(info_t *info, int all)
{
	freeStringArray(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeList(&(info->env));
		if (info->history)
			freeList(&(info->history));
		if (info->alias)
			freeList(&(info->alias));
		freeStringArray(info->environ);
			info->environ = NULL;
		safely_free_pointer((void **)info->cmd_buf);
		if (info->readfd > 2)
		close(info->readfd);
		_putchar(FLUSH_BUFFER);
	}
}
