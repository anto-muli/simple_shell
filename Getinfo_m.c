#include "shell.h"
/**
 * wipe_info - This function, startss an info_t structure
 * @info: The address of the struct to be initialized.
 */
void wipe_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * place_info - This function, startss an info_t structure
 * @info: The address of the initialized structure
 * @av: The argument vector to populate the struct.
 */
void place_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = split_str(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strclone(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		change_alias(info);
		change_vars(info);
	}
}

/**
 * release_info - releases memory associated with fields of the info_t struct.
 * @info: The address of the struct whose fields are to be freed.
 * @all: A boolean indicating whether to free all fields (true)
 * or a subset (false).
 */
void release_info(info_t *info, int all)
{
	free_string_array(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			release_list(&(info->env));
		if (info->history)
			release_list(&(info->history));
		if (info->alias)
			release_list(&(info->alias));
		free_string_array(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
