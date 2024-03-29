#include "shell.h"

/**
 * _setenv - Create a new environment variable or update an existing one.
 * @info: Structure containing relevant information,
 * used for function prototype consistency.
 * @var: The name of the environment variable.
 * @value: The value to set for the environment variable.
 * Return: Always returns 0.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *t;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	concatenate_strings(buf, "=");
	concatenate_strings(buf, value);
	node = info->env;
	while (node)
	{
		t = check_starts_with(node->stringValue, var);
		if (t && *t == '=')
		{
			free(node->stringValue);
			node->stringValue = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->nextNode;
	}
	addNodeAtEnd(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

/**
 * _unsetenv - Deletes an environment variable.
 * @info: Structure containing relevant information,
 * used for function prototype consistency.
 * @var: The name of the environment variable to remove.
 * Return: Returns 1 if the variable is deleted, otherwise 0.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t x = 0;
	char *t;

	if (!node || !var)
		return (0);

	while (node)
	{
		t = check_starts_with(node->stringValue, var);
		if (t && *t == '=')
		{
			info->env_changed = deleteNodeAtIndex(&(info->env), x);
			x = 0;
			node = info->env;
			continue;
		}
		node = node->nextNode;
		x++;
	}
	return (info->env_changed);
}

/**
 * get_environ - Returns copy of string array containing environment variables.
 * @info: Structure containing relevant information,
 * used for function prototype consistency.
 * Return: Always returns 0.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = convert_list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}
