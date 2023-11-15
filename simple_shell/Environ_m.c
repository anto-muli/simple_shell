#include "shell.h"

/**
 * _populateEnvironmentList - populates an environment linked list
 * @info: Structure containing potential arguments. Maintained for
 *                      consistent function signature.
 * Return: Always returns 0
 */
int _populateEnvironmentList(info_t *info)
{
	list_t *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		addNodeAtEnd(&node, environ[x], 0);
	info->environmentList = node;
	return (0);
}
/**
 * _myunsetenv - Delete an environment variable
 * @info: Structure containing potential arguments. Preserved for
 * consistent function signature.
 * Return: Always returns 0
 */
int _myunsetenv(info_t *info)
{
	int x;

	if (info->argc == 1)
	{
		_eputs("less Args.\n");
		return (1);
	}
	for (x = 1; x <= info->argc; x++)
		_unsetenv(info, info->argv[x]);
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
		_eputs("Incorrect # of args\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}



/**
 * _retrieveEnvironmentValue - obtains the value of an environment variable
 * @info: Structure containing potential arguments.
 * Preserved for consistency.
 * @variableName: Name of the environment variable
 *
 * Return: The corresponding value or NULL if not found
 */
char *_retrieveEnvironmentValue(info_t *info, const char *variableName)
{
	list_t *currentNode = info->environmentList;
	char *t;

	while (currentNode)
	{
		t = check_starts_with(currentNode->stringValue, variableName);
		if (t && *t)
			return (t);
		currentNode = currentNode->nextNode;
	}
	return (NULL);
}

/**
 * _printEnvironment - displays the current environment variables
 * @info: Structure containing possible arguments. Maintained for
 *                consistent function signature.
 * Return: Always returns 0
 */
int _printEnvironment(info_t *info)
{
	printStringList(info->environmentVariables);
	return (0);
}
