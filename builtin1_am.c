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
	char *aliasStart, aliasChar;
	int result;

	aliasStart = my_strchr(string, '=');
	if (!aliasStart)
		return (1);
	aliasChar = *aliasStart;
	*aliasStart = '\0';
	result = deleteNodeAtIndex(&(info->alias),
			find_node_index(info->alias,
				find_node_with_prefix(info->alias, string, -1)));
	*aliasStart = aliasChar;
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
	char *equalSignPos;

	equalSignPos = my_strchr(str, '=');
	if (!equalSignPos)
		return (1);
	if (!*++equalSignPos)
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
	char *equalSignPos = NULL, *aliasStart = NULL;

	if (node)
	{
		equalSignPos = my_strchr(node->stringValue, '=');
		for (aliasStart = node->stringValue;
				aliasStart <= equalSignPos; aliasStart++)
			_putchar(*aliasStart);
		_putchar('\'');
		_puts(equalSignPos + 1);
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
	int i = 0;
	char *equalSignPos = NULL;
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
	for (i = 1; info->argv[i]; i++)
	{
		equalSignPos = my_strchr(info->argv[i], '=');
		if (equalSignPos)
			set_alias(info, info->argv[i]);
		else
			print_alias(find_node_with_prefix(info->alias, info->argv[i], '='));
	}
	return (0);
}

