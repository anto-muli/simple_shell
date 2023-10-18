#include "shell.h"

/**
 * fetch_environ - Returns a copy of strn array
 * containing environment variables.
 * @info: Structure contains relevant information,
 * used for function prototype consistency.
 * Return: Always returns 0.
 */
char **fetch_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = convert_list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Deletes an environ variable
 * @info: Structure contains relevant info
 * used for function prototype consistency.
 * @var: The name of the environment variable to remove.
 * Return: Returns 1 if the variable is deleted, otherwise 0.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = str_starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = remove_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Create a new environment variable or update an existing one.
 * @info: Struct contains relevant information,
 * used for function prototype consistency.
 * @var: The name of the environment variable.
 * @value: The value to set for the environment variable.
 * Return: Always returns 0.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlength(var) + _strlength(value) + 2);
	if (!buf)
		return (1);
	_strcopy(buf, var);
	_strconcatenate(buf, "=");
	_strconcatenate(buf, value);
	node = info->env;
	while (node)
	{
		p = str_starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	attach_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
