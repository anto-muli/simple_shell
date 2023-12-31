#include "shell.h"

/**
 * generate_env_list - generates an environment linked list
 * @info: Structure containing possible argss kept for
 * consistent functs signature.
 * Return: Always returns 0
 */
int generate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		attach_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
/**
 * _myunsetenv - Deletes all environ variables
 * @info: Structure containing possible args. Preserved for
 * consistent function signature.
 * Return: Always returns 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_displaystr("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * _mysetenv - Create a new environment variable
 * or modify an existing one
 * @info: Structure containing potential arguments. Maintained for
 * consistent function signature.
 * Return: Always returns 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_displaystr("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _fetchenv - obtains the value of an environment variable
 * @info: Structure containing possible args
 * Preserved for consistency.
 * @name: Name of the environment variable
 *
 * Return: The corresponding value or NULL if not found
 */
char *_fetchenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = str_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _findenv - displays the current environment variables
 * @info: Structure containing possible arguments. Maintained for
 * consistent function signature.
 * Return: Always returns 0
 */
int _findenv(info_t *info)
{
	display_list_str(info->env);
	return (0);
}
