#include "shell.h"

/**
 * change_string - Replaces a string with a new one.
 * @old: Address of the old string to be replaced.
 * @new: The new string to replace the old one.
 *
 * Return: 1 if the replacement is successful, 0 otherwise.
 */
int change_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * change_vars - changes variables in the tokenized strn
 * @info: Pointer to the parameter struct.
 *
 * Return: 1 if variables are replaced, 0 otherwise.
 */
int change_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcompare(info->argv[i], "$?"))
		{
			change_string(&(info->argv[i]),
				_strclone(change_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcompare(info->argv[i], "$$"))
		{
			change_string(&(info->argv[i]),
				_strclone(change_number(getpid(), 10, 0)));
			continue;
		}
		node = first_node(info->env, &info->argv[i][1], '=');
		if (node)
		{
			change_string(&(info->argv[i]),
				_strclone(_strchars(node->str, '=') + 1));
			continue;
		}
		change_string(&info->argv[i], _strclone(""));

	}
	return (0);
}

/**
 * test_chain - Determine to continue chaining based on last command's status.
 * @info: Pointer to the parameter structure
 * @buf: Character buffer.
 * @p: Address of the current position in buffer
 * @i: Starting position in buffer
 * @len: Length of buffer
 *
 * Return: return void
 */
void test_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * confirm_chain - Checks current character in the buffer
 * is a chaining delimiter.
 * @info: Pointer to the parameter structure
 * @buf: Character buf
 * @p: Address of the current position in buffer
 *
 * Return: 1 if it is a chaining delimiter or 0 if not
 */
int confirm_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * change_alias - changes aliases in strings which are tokenized
 * @info: the para structure
 *
 * Return:  one if it has been replaced and 0 if not
 */
int change_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = first_node(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchars(node->str, '=');
		if (!p)
			return (0);
		p = _strclone(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}
