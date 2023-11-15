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
	int x = 0, l = 0;

	for (l = 0, x = start; x < stop; x++)
		if (pathstr[x] != ':')
			buf[l++] = pathstr[x];
	buf[l] = 0;
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
	int x = 0, currentPosition = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && check_starts_with(cmd, "./"))
	{
		if (isExecutableCommand(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[x] || pathstr[x] == ':')
		{
			path = duplicateCharacters(pathstr, currentPosition, x);
			if (!*path)
				concatenate_strings(path, cmd);
			else
			{
				concatenate_strings(path, "/");
				concatenate_strings(path, cmd);
			}
			if (isExecutableCommand(info, path))
				return (path);
			if (!pathstr[x])
				break;
			currentPosition = x;
		}
		x++;
	}
	return (NULL);
}
