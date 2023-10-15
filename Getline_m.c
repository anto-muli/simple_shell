#include "shell.h"

/**
 * input_buf - Read and process input, buffering chained commands.
 * @info: A parameter struct
 * @buf: A pointer to the input buffer
 * @len: A pointer to the length variable
 *
 * Return: The number of bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t v = 0;
	size_t buffer_length = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*safely_free_pointer((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		v = getline(buf, &buffer_length, stdin);
#else
		v = _getline(info, buf, &buffer_length);
#endif
		if (v > 0)
		{
			if ((*buf)[v - 1] == '\n')
			{
				(*buf)[v - 1] = '\0'; /* remove trailing newline */
				v--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			addtoHistoryList(info, *buf, info->histcount++);
			/* if (my_strchr(*buf, ';')) is this a command chain? */
			{
				*len = v;
				info->cmd_buf = buf;
			}
		}
	}
	return (v);
}

/**
 * get_input - Retrieve input, excluding the newline character.
 * @info: A parameter struct.
 *
 * Return: The number of bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t x, k, len;
	ssize_t v = 0;
	char **buff_ptr = &(info->arg), *ret_ptr;

	_putchar(FLUSH_BUFFER);
	v = input_buf(info, &buf, &len);

	if (v == -1) /* EOF */
		return (-1);

	if (len) /* There are still commands remaining in the chain buffer */
	{
		k = x; /* Initialize a new iterator at the current position of the buffer */
		ret_ptr = buf + x; /* Retrieve the pointer for the return value */
		check_chain(info, buf, &k, x, len);
		while (k < len) /* Continue iterating till u get a semicolon or end */
		{
			if (is_chain(info, buf, &k))
				break;
			k++;
		}
		x = k + 1; /* increment past nulled ';'' */
		if (x >= len) /* reached end of buffer? */
		{
			x = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}
		*buff_ptr = ret_ptr; /* pass back pointer to current command position */
		return (_strlen(ret_ptr));  /* return length of current command */
	}
	*buff_ptr = buf; /* else not a chain, pass back buffer from _getline() */
	return (v); /* return length of buffer from _getline() */
}

/**
 * read_buf - Read data into a buffer.
 * @info: A parameter struct.
 * @buf: The buffer to read into.
 * @x: A pointer to the size.
 *
 * Return: The number of bytes read (v).
 */
ssize_t read_buf(info_t *info, char *buf, size_t *x)
{
	ssize_t v = 0;

	if (*x)
		return (0);

	v = read(info->readfd, buf, READ_BUF_SIZE);

	if (v >= 0)
		*x = v;
	return (v);
}

/**
 * _getline - Read the next line of input from STDIN.
 * @info: A parameter struct.
 * @pt: Address of a pointer to the buffer, preallocated or NULL.
 * @length: Size of the preallocated ptr buffer if not NULL.
 *
 * Return: The number of characters read (y), or -1 on failure.
 */
int _getline(info_t *info, char **pt, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t x, len;
	size_t l;
	ssize_t v = 0, y = 0;
	char *t = NULL, *new_ptr = NULL, *b;

	t = *pt;
	if (t && length)
		y = *length;

	if (x == len)
		x = len = 0;

	v = read_buf(info, buf, &len);
	if (v == -1 || (v == 0 && len == 0))
		return (-1);
	b = my_strchr(buf + x, '\n');
	l = b ? 1 + (unsigned int)(b - buf) : len;

	new_ptr = customReallocate(t, y, y ? y + l : l + 1);
	if (!new_ptr) /* MALLOC FAILURE! */
		return (t ? free(t), -1 : -1);

	if (y)
		_strncat(new_ptr, buf + x, l - x);
	else
		_strncpy(new_ptr, buf + x, l - x + 1);
	y += l - x;
	x = l;
	t = new_ptr;

	if (length)
		*length = y;
	*pt = t;
	return (y);
}

/**
 * sigintHandler - Handle the SIGINT signal to block Ctrl-C.
 * @sig_num: The signal number (unused).
 *
 * Return: Void.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH_BUFFER);
}
