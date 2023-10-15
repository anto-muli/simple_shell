#include "shell.h"

/**
 * replace_string - Replaces a string with a new one.
 * @old: Address of the old string to be replaced.
 * @new: The new string to replace the old one.
 *
 * Return: 1 if the replacement is successful, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * replace_vars - Replaces variables in the tokenized string.
 * @info: Pointer to the parameter struct.
 *
 * Return: 1 if variables are replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int x = 0;
	list_t *currentnode;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

	if (!compare_strings(info->argv[x], "$?"))
	{
		replace_string(&(info->argv[x]),
			_strdup(convert_number(info->status, 10, 0)));
		continue;
	}
	if (!compare_strings(info->argv[x], "$$"))
	{
		replace_string(&(info->argv[x]),
			_strdup(convert_number(getpid(), 10, 0)));
		continue;
	}
	currentnode = find_node_with_prefix(info->env, &info->argv[x][1], '=');
	if (currentnode)
	{
		replace_string(&(info->argv[x]),
			_strdup(my_strchr(currentnode->string, '=') + 1));
		continue;
	}
	replace_string(&info->argv[x], _strdup(""));
	}
	return (0);
}

/**
 * check_chain - Determine to continue chaining based on last command's status.
 * @info: Pointer to the parameter struct.
 * @buf: Character buffer.
 * @t: Address of the current position in 'buf'.
 * @x: Starting position in 'buf'.
 * @len: Length of 'buf'.
 *
 * Return: Void.
 */
void check_chain(info_t *info, char *buf, size_t *t, size_t x, size_t len)
{
	size_t k = *t;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[x] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[x] = 0;
			k = len;
		}
	}

	*t = k;
}

/**
 * is_chain - Checks current character in the buffer is a chaining delimiter.
 * @info: Pointer to the parameter struct.
 * @buf: Character buffer.
 * @t: Address of the current position in 'buf'.
 *
 * Return: 1 if it is a chaining delimiter, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *t)
{
	size_t k = *t;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';') /* found end of this command */
	{
		buf[k] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*t = k;
	return (1);
}

/**
 * replace_alias - replaces aliases in strings which are tokenized
 * @info: the para structure
 *
 * Return:  one if it has been replaced and 0 if not
 */
int replace_alias(info_t *info)
{
	int x;
	list_t *currentnode;
	char *t;

	for (x = 0; x < 10; x++)
	{
		currentnode = find_node_with_prefix(info->alias, info->argv[0], '=');
		if (!currentnode)
			return (0);
		free(info->argv[0]);
		t = my_strchr(currentnode->string, '=');
		if (!t)
			return (0);
		t = _strdup(t + 1);
		if (!t)
			return (0);
		info->argv[0] = t;
	}
	return (1);
}
