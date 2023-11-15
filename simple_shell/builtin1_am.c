#include "shell.h"
/**
  * _myhistory - is responsible for,
  * showing the list of previously executed commands.
  * Each command is displayed on a separate line,
  * accompanied by line numbers starting from 0.
  * @info: A structure that holds possible arguments,
  * ensuring consistent function prototype.
  * Return: Always returns 0.
  */
int _myhistory(info_t *info)
{
	print_linked_list(info->history);
	return (0);
}

/**
  * unset_alias - assigns an alias to a string.
  *
  * @info: A structure containing relevant parameters.
  * @string: The string representing the alias.
  *
  * Return: Returns 0 on success, 1 on error.
  */
int unset_alias(info_t *info, char *string)
{
	char *t, b;
	int result;

	t = my_strchr(string, '=');
	if (!t)
		return (1);
	b = *t;
	*t = '\0';
	result = deleteNodeAtIndex(&(info->alias),
			find_node_index(info->alias, find_node_with_prefix(info->alias, string, -1)));
	*t = b;
	return (result);
}
/**
 * set_alias - associates an alias with a string.
 *
 * @info: A structure containing relevant parameters.
 * @str: The string representing the alias.
 *
 * Return: Returns 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *t;

	t = my_strchr(str, '=');
	if (!t)
		return (1);
	if (!*++t)
		return (unset_alias(info, str));
	unset_alias(info, str);
	return (addNodeAtEnd(&(info->alias), str, 0) == NULL);
}
/**
  * print_alias -displays an alias string.
  *
  * @node: The alias node containing the string.
  *
  * Return: Returns 0 on success, 1 on error.
  */
int print_alias(list_t *node)
{
	char *t = NULL, *z = NULL;

	if (node)
	{
		t = my_strchr(node->stringValue, '=');
		for (z = node->stringValue;
				z <= t; z++)
			_putchar(*z);
		_putchar('\'');
		_puts(t + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
  * _myalias - emulates the behavior of,
  * the alias command (see 'man alias').
  *
  * @info: A structure that potentially holds function arguments,
  * ensuring a consistent function prototype.
  * Return: Always returns 0.
  */
int _myalias(info_t *info)
{
	int x = 0;
	char *t = NULL;
	list_t *currentAliasNode = NULL;

	if (info->argc == 1)
	{
		currentAliasNode = info->alias;
		while (currentAliasNode)
		{
			print_alias(currentAliasNode);
			currentAliasNode = currentAliasNode->nextNode;
		}
		return (0);
	}
	for (x = 1; info->argv[x]; x++)
	{
		t = my_strchr(info->argv[x], '=');
		if (t)
			set_alias(info, info->argv[x]);
		else
			print_alias(find_node_with_prefix(info->alias, info->argv[x], '='));
	}
	return (0);
}

