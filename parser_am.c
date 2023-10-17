#include "shell.h"
/**
 * is_cmd - Determines whether a file at the given path
 * is an executable command.
 *
 * @info: A pointer to the info struct (unused in this function).
 * @path: The path to the file.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * dup_chars - a range of characters from a given PATH string.
 *
 * @pathstr: The input PATH string.
 * @start: The starting index of the range.
 * @stop: The stopping index of the range.
 * Return: A pointer to a new buffer containing the duplicated characters.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
		static char buf[1024];
		int i = 0, k = 0;

		for (k = 0, i = start; i < stop; i++)
			if (pathstr[i] != ':')
				buf[k++] = pathstr[i];
		buf[k] = 0;
		return (buf);
}

/**
 * find_path - find all path of a command within the PATH string.
 *
 * @info: A pointer to the info struct.
 * @pathstr: The PATH string containing directories.
 * @cmd: The command to find.
 * Return: A pointer to the full path of 'cmd' if found, or NULL if not found.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlength(cmd) > 2) && str_starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strconcatenate(path, cmd);
			else
			{
				_strconcatenate(path, "/");
				_strconcatenate(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
