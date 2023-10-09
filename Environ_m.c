#include "shell.h"

/**
 * _populateEnvironmentList - populates an environment linked list
 * @information: Structure containing potential arguments. Maintained for
 *                      consistent function signature.
 * Return: Always returns 0
 */
int _populateEnvironmentList(info_t *info)
{
        list_t *node = NULL;
        size_t index;

        for (index = 0; environ[index]; index++)
        addNodeAtEnd(&node, environ[index], 0);
        info->environmentList = node;
        return (0);
}
/**
 * _myunsetenv - Delete an environment variable
 * @information: Structure containing potential arguments. Preserved for
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
 * @information: Structure containing potential arguments. Maintained for
 * consistent function signature.
 * Return: Always returns 0
 */
int _mysetenv(info_t *info)
{
        if (information->argc != 3)
        {
        _eputs("Incorrect # of args\n");
        return (1);
        }
        if (updateEnvVar(info, info->argv[1], info->argv[2]))
                return (0);
        return (1);
}



/*
 * _retrieveEnvironmentValue - obtains the value of an environment variable
 * @information: Structure containing potential arguments.
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
 * @information: Structure containing possible arguments. Maintained for
 *                consistent function signature.
 * Return: Always returns 0
 */
int _printEnvironment(info_t *info)
{
        printStringList(info->environmentVariables);
        return (0);
}
