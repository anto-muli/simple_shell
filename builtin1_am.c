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
	int turn;

	t = my_strchr(string, '=');
	if (!t)
		return (1);
	b = *t;
	*t = '\0';
	turn = deleteNodeAtIndex(&(info->alias),
			find_node_index(info->alias, find_node_with_prefix(info->alias, string, -1)));
	*t = b;
	return (turn);
}
/**
 * set_alias - associates an alias with a string.
 *
 * @info: A structure containing relevant parameters.
 * @string: The string representing the alias.
 *
 * Return: Returns 0 on success, 1 on error
 */
int set_alias(info_t *info, char *string)
{
	char *t;

	t = my_strchr(string, '=');
	if (!t)
		return (1);
	if (!*++t)
		return (unset_alias(info, string));
	unset_alias(info, string);
	return (addNodeAtEnd(&(info->alias), string, 0) == NULL);
}
/**
  * print_alias -displays an alias string.
  *
  * @currentnode: The alias node containing the string.
  *
  * Return: Returns 0 on success, 1 on error.
  */
int print_alias(list_t *currentnode)
{
	char *t = NULL, *z = NULL;

	if (currentnode)
	{
		t = my_strchr(currentnode->string, '=');
		for (z = currentnode->string;
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
	list_t *currentnode = NULL;

	if (info->argc == 1)
	{
		currentnode = info->alias;
		while (currentnode)
		{
			print_alias(currentnode);
			currentnode = currentnode->nextNode;
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

