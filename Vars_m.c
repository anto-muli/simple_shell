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
	int a = 0;
	list_t *node;

	for (a = 0; info->argv[a]; a++)
	{
		if (info->argv[a][0] != '$' || !info->argv[a][1])
			continue;

	if (!compare_strings(info->argv[a], "$?"))
	{
		replace_string(&(info->argv[a]),
			_strdup(convert_to_string(info->status, 10, 0)));
		continue;
	}
	if (!compare_strings(info->argv[a], "$$"))
	{
		replace_string(&(info->argv[a]),
			_strdup(convert_to_string(getpid(), 10, 0)));
		continue;
	}
	node = find_node_with_prefix(info->env, &info->argumentValues[a][1], '=');
	if (node)
	{
		replace_string(&(info->argv[a]),
			_strdup(my_strchr(node->stringValue, '=') + 1));
		continue;
	}
	replace_string(&info->argv[a], _strdup(""));
	}
	return (0);
}

/**
 * check_chain - Determine to continue chaining based on last command's status.
 * @info: Pointer to the parameter struct.
 * @buf: Character buffer.
 * @p: Address of the current position in 'buf'.
 * @i: Starting position in 'buf'.
 * @len: Length of 'buf'.
 *
 * Return: Void.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
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
 * is_chain - Checks current character in the buffer is a chaining delimiter.
 * @info: Pointer to the parameter struct.
 * @buf: Character buffer.
 * @p: Address of the current position in 'buf'.
 *
 * Return: 1 if it is a chaining delimiter, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
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
 * replace_alias - replaces aliases in strings which are tokenized
 * @information: the para structure
 *
 * Return:  one if it has been replaced and 0 if not
 */
int replace_alias(info_t *info)
{
	int w;
	list_t *nextNode;
	char *x;

	for (w = 0; w < 10; w++)
	{
		nextNode = node_starts_with(info->alias,info->argv[0], '=');
		if (!nextNode)
			return (0);
		free(info->argv[0]);
		x = my_strchr(nextNode->string, '=');
		if (!x)
			return (0);
		x = _strdup(x + 1);
		if (!x)
			return (0);
		info->argv[0] = x;
	}
	return (1);
}
