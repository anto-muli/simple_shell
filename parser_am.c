#include "shell.h"
/**
 * isExecutableCommand - Determines whether a file at the given path
 * is an executable command.
 *
 * @info: A pointer to the info struct (unused in this function).
 * @path: The path to the file.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int isExecutableCommand(info_t *info, char *path)
{
	struct stat fileStat;

	(void)info;
	if (!path || stat(path, &fileStat))
		return (0);

	if (fileStat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * duplicateCharacters - a range of characters from a given PATH string.
 *
 * @pathstr: The input PATH string.
 * @start: The starting index of the range.
 * @stop: The stopping index of the range.
 * Return: A pointer to a new buffer containing the duplicated characters.
 */
char *duplicateCharacters(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int inputIndex = 0; bufferIndex = 0;

	for (bufferIndex = 0, inputIndex = start; inputIndex < stop; inputIndex++)
		if (pathstr[inputIndex] != ':')
			buf[bufferIndex++] = pathstr[inputIndex];
	buf[bufferIndex] = 0;
	return (buf);
}

/**
 * findCommandPath - find all path of a command within the PATH string.
 *
 * @info: A pointer to the info struct.
 * @pathstr: The PATH string containing directories.
 * @cmd: The command to find.
 * Return: A pointer to the full path of 'cmd' if found, or NULL if not found.
 */
char *findCommandPath(info_t *info, char *pathstr, char *cmd)
{
	int currentIndex = 0, currentPosition = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((strlen(cmd) > 2) && check_starts_with(cmd, "./"))
	{
		if (isExecutableCommand(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[currentIndex] || pathstr[currentIndex] == ':')
		{
			path = duplicateCharacters(pathstr, currentPosition, currentIndex);
			if (!*path)
				strcat(path, cmd);
			else
			{
				strcat(path, "/");
				strcat(path, cmd);
			}
			if (isExecutableCommand(info, path))
				return (path);
			if (!pathstr[currentIndex])
				break;
			currentPosition = currentIndex;
		}
		currentIndex++;
	}
	return (NULL);
}
