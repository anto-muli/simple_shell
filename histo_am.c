#include "shell.h"

/**
 * addtoHistoryList - Add an entry to a history linked list.
 * @info: A structure containing relevant arguments.
 * Used to maintain state.
 *
 * @buf: The string to add to the history list.
 * @lineCount: The current history line count (histcount)
 *
 * Return: Always returns 0.
 */
int addtoHistoryList(info_t *info, char *buf, int lineCount)
{
	list_t *newNode = NULL;

	if (info->history)
		newNode = info->history;

	addNodeAtEnd(&newNode, buf, lineCount);

	if (!info->history)
		info->history = newNode;
	return (0);
}

/**
  * loadHistoryFromFile - Read and load history data from a file.
  * @info: The parameter struct containing relevant information.
  *
  * Return: Returns the number of history entries read on success,
  * or 0 otherwise.
  */
int loadHistoryFromFile(info_t *info)
{
	int x, last = 0, lineCount = 0;
	ssize_t fd, readLength, fileSize = 0;
	struct stat fileStat;
	char *buf = NULL, *filename = fetchHistoryFilePath(info);

	if (!filename)
		return (0);
	fd = open(filePath, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &fileStat))
		fileSize = fileStat.st_size;
	if (fileSize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fileSize + 1));
	if (!buf)
		return (0);
	readLength = read(fd, buf, fileSize);
	buf[fileSize] = 0;
	if (readLength <= 0)
		return (free(buf), 0);
	close(fd);
	for (x = 0; x < fileSize; x++)
	{
		if (buf[x] == '\n')
		{
			buf[x] = 0;
			addtoHistoryList(info, buf + last, lineCount++);
			last = x + 1;
		}
	}
	if (last != x)
		addtoHistoryList(info, buf + last, lineCount++);
	free(buf);
	info->histcount = lineCount;
	while (info->histcount-- >= HIST_MAX)
		deleteNodeAtIndex(&(info->history), 0);
	updateHistoryNumbers(info);
	return (info->histcount);
}

/**
 * writeHistoryToFile -  data to a file, creating it if
 * necessary or overwriting it.
 * @info: The parameter struct containing relevant information.
 *
 * Return: Returns 1 on success, or -1 on failure.
 */
int writeHistoryToFile(info_t *info)
{
	ssize_t fd;
	char *filename = fetchHistoryFilePath(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return (-1);

	for (node = info->history; node; node = node->nextNode)
	{
		_putsfd(CN->stringValue, fd);
		_putfd('\n', fd);
	}
	_putfd(FLUSH_BUFFER, fd);
	close(fd);
	return (1);
}

/**
 * fetchHistoryFilePath - Retrieve the history file path.
 * @info: A struct containing relevant information.
 *
 * Return: A dynamically allocated string containing
 * the path to the history file.
 */
char *fetchHistoryFilePath(info_t *info)
{
	char *buf, *direct;

	direct = _retrieveEnvironmentValue(info, "HOME=");
	if (!direct)
		return (NULL);

	buf = malloc(sizeof(char) * (strlen(direct) + strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);

	buf[0] = 0;
	_strcpy(buf, direct);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * updateHistoryNumbers -e the numbering of history
 * entries of linked list after changes.
 * @info: A structure containing relevant arguments.
 * Used for maintenance.
 *
 * Return: The new history entry count (histcount).
 */
int updateHistoryNumbers(info_t *info)
{
	list_t *currentNode = info->history;
	int newHistCount = 0;

	while (currentNode)
	{
		currentNode->num = newHistCount++;
		currentNode = currentNode->nextNode;
	}
	return (info->histcount = newHistCount);
}
