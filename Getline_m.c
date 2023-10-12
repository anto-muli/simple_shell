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
        ssize_t a = 0;
        size_t buffer_length = 0;

        if (!*len) /* if nothing left in the buffer, fill it */
        {
                /*bfree((void **)info->cmd_buf);*/
                free(*buf);
                *buf = NULL;
                signal(SIGINT, sigintHandler);

#if USE_GETLINE
                a = getline(buf, &buffer_length, stdin);
#else
                a = _getline(info, buf, &buffer_length);
#endif

                if (a > 0)
                {
                        if ((*buf)[a - 1] == '\n')
                        {
                                (*buf)[a - 1] = '\0'; /* remove trailing newline */
                                a--;
                        }
                        info->linecount_flag = 1;
                        remove_first_comment(*buf);
                        addtoHistoryList(info, *buf, info->histcount++);
                        /* if (my_strchr(*buf, ';')) is this a command chain? */
                        {
                                *len = a;
                                info->cmd_buf = buf;
                        }
                }
        }
        return (a);
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
        static size_t c_pos, next_pos, buff_len;
        ssize_t r = 0;
        char **buff_ptr = &(info->arg), *ret_ptr;

        _putchar(FLUSH_BUFFER);
        r = input_buf(info, &buf, &buff_len);

        if (r == -1) /* EOF */
        return (-1);

        if (buff_len) /* There are still commands remaining in the chain buffer */
        {
        next_pos = c_pos; /* Initialize a new iterator at the current position of the buffer */
        ret_ptr = buf + c_pos; /* Retrieve the pointer for the return value */

        check_chain(info, buf, &next_pos, c_pos, buff_len);

        while (next_pos < buff_len) /* Continue iterating until reaching a semicolon or the end */
        {
        if (is_chain(info, buf, &next_pos))
                break;
        next_pos++;
        }

        c_pos = next_pos + 1; /* increment past nulled ';'' */

        if (c_pos >= buff_len) /* reached end of buffer? */
        {
                c_pos = buff_len = 0; /* reset position and length */
                info->cmd_buf_type = CMD_NORM;
        }

        *buff_ptr = ret_ptr; /* pass back pointer to current command position */
        return (_strlen(ret_ptr));  /* return length of current command */
        }

        *buff_ptr = buf; /* else not a chain, pass back buffer from _getline() */
        return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - Read data into a buffer.
 * @info: A parameter struct.
 * @buf: The buffer to read into.
 * @a: A pointer to the size.
 *
 * Return: The number of bytes read (b).
 */
ssize_t read_buf(info_t *info, char *buf, size_t *a)
{
        ssize_t b = 0;

        if (*a)
        return (0);

        b = read(info->readfd, buf, READ_BUF_SIZE);

        if (b >= 0)
                *a = b;

        return (b);
}

/**
 * _getline - Read the next line of input from STDIN.
 * @info: A parameter struct.
 * @pointer: Address of a pointer to the buffer, preallocated or NULL.
 * @length: Size of the preallocated ptr buffer if not NULL.
 *
 * Return: The number of characters read (s), or -1 on failure.
 */
int _getline(info_t *info, char **pointer, size_t *length)
{
        static char buf[READ_BUF_SIZE];
        static size_t c_pos, buff_len;
        size_t k;
        ssize_t r = 0, char_read = 0;
        char *p = NULL, *new_ptr = NULL, *nline_pos;

        p = *pointer;
        if (p && length)
                char_read = *length;

        if (c_pos == buff_len)
                c_pos = buff_len = 0;

        r = read_buf(info, buf, &buff_len);
        if (r == -1 || (r == 0 && buff_len == 0))
        return (-1);

        nline_pos = my_strchr(buf + c_pos, '\n');
        k = nline_pos ? 1 + (unsigned int)(nline_pos - buf) : buff_len;

        new_ptr = customReallocate(p, char_read, char_read ?
                        char_read + k : k + 1);

        if (!new_ptr) /* MALLOC FAILURE! */
                return (p ? free(p), -1 : -1);

        if (char_read)
                _strncat(new_ptr, buf + c_pos, k - c_pos);
        else
                _strncpy(new_ptr, buf + c_pos, k - c_pos + 1);

        char_read += k - c_pos;
        c_pos = k;
        p = new_ptr;

        if (length)
                *length = char_read;
        *pointer = p;
        return (char_read);
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
