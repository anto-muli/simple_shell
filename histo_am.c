#include "shell.h"

/**
 * create_histlist - Add an entry to a history linked list.
 * @info: A structure containing relevant arguments.
 * Used to maintain state.
 *
 * @buf: The string to add to the history list.
 * @linecount: The current history line count (histcount)
 *
 * Return: Always returns 0.
 */
int create_histlist(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	attach_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
  * scan_hist - Read and load history data from a file.
  * @info: The parameter struct containing relevant information.
  *
  * Return: Returns the number of history entries read on success,
  * or 0 otherwise.
  */
int scan_hist(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = fetch_histfile(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			create_histlist(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		create_histlist(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		remove_node_at_index(&(info->history), 0);
	reorder_hist(info);
	return (info->histcount);
}

/**
 * record_hist -  data to a file, creating it if
 * necessary or overwriting it.
 * @info: The parameter struct containing relevant information.
 *
 * Return: Returns 1 on success, or -1 on failure.
 */
int record_hist(info_t *info)
{
	ssize_t fd;
	char *filename = fetch_histfile(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_displaysfd(node->str, fd);
		_displayfd('\n', fd);
	}
	_displayfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * fetch_histfile - Retrieve the history file path.
 * @info: A struct containing relevant information.
 *
 * Return: A dynamically allocated string containing
 * the path to the history file.
 */
char *fetch_histfile(info_t *info)
{
	char *buf, *dir;

	dir = _fetchenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlength(dir) + _strlength(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcopy(buf, dir);
	_strconcatenate(buf, "/");
	_strconcatenate(buf, HIST_FILE);
	return (buf);
}
/**
 * reorder_hist -e the numbering of history
 * entries of linked list after changes.
 * @info: A structure containing relevant arguments.
 * Used for maintenance.
 *
 * Return: The new history entry count (histcount).
 */
int reorder_hist(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
