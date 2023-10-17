#include "shell.h"
/**
  * _ourhist - is responsible for,
  * showing the list of previously executed commands.
  * Each command is displayed on a separate line,
  * accompanied by line numbers starting from 0.
  * @info: A structure that holds possible arguments,
  * ensuring consistent function prototype.
  * Return: Always returns 0.
  */
int _ourhist(info_t *info)
{
	display_list(info->history);
	return (0);
}

/**
  * undo_alias - assigns an alias to a string.
  *
  * @info: A structure containing relevant parameters.
  * @str: The string representing the alias.
  *
  * Return: Returns 0 on success, 1 on error.
  */
int undo_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _locatechar(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = remove_node_at_index(&(info->alias),
			fetch_node_index(info->alias, first_node(info->alias, str, -1)));
	*p = c;
	return (ret);
}
/**
 * fix_alias - associates an alias with a string.
 *
 * @info: A structure containing relevant parameters.
 * @str: The string representing the alias.
 *
 * Return: Returns 0 on success, 1 on error
 */
int fix_alias(info_t *info, char *str)
{
	char *p;

	p = _locatechar(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (undo_alias(info, str));

	undo_alias(info, str);
	return (attach_node_end(&(info->alias), str, 0) == NULL);
}
/**
  * display_alias -displays an alias string.
  *
  * @node: The alias node containing the string.
  *
  * Return: Returns 0 on success, 1 on error.
  */
int display_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _locatechar(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
  * _ouralias - emulates the behavior of,
  * the alias command (see 'man alias').
  *
  * @info: A structure that potentially holds function arguments,
  * ensuring a consistent function prototype.
  * Return: Always returns 0.
  */
int _ouralias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			display_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _locatechar(info->argv[i], '=');
		if (p)
			fix_alias(info, info->argv[i]);
		else
			display_alias(first_node(info->alias, info->argv[i], '='));
	}
	return (0);
}
