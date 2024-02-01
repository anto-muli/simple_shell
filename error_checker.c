#include "shell.h"
/**
  * _displaystr - This function is responsible for displaying a given string.
  * @str: The input string to be printed.
  *
  * Description: function iterates through the chars in the input string 'str'
  * and calls another function '_displaychar' to print each char
  * If input string
  * is empty or null, it simply returns without doing anything
   */
void _displaystr(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_displaychar(str[i]);
		i++;
	}
}
/**
  * _displaychar - function writes the character 'c' to
  * the standard error stream.
  * @c: The character to be printed
  *
  * Description: function is designed to write a character 'c' to the standard
  * error stream (stderr). It utilizes an internal buffer 'buf' to store chars
  * before flushing them to stderr
  *Return: When the character 'c' is equal to BUF_FLUS
  * or the buffer is full, the contents of the buffer are written to stderr
  * On success, returns 1; on error, it returns -1 and sets errno appropriately
   */
int _displaychar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
  * _displayfd - This function writes the char 'c' to the file descriptor 'fd'.
  * @c: The character to be printed.
  * @fd: The file descriptor to which the character is written.
  *
  * Description: This function writes a char 'c' to the file descriptor
  * 'fd'. Uses internal buffer 'buf' to temporarily store char before flushing
  * them to specified file descriptor
  *Return: If the char 'c' is equal to BUF_FLUSH or
  * buffer is full, the contents of buffer are written to the file descriptor.
  * On success, returns 1; on error, it returns -1 and
  *sets errno appropriately.
  */
int _displayfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
  * _displaysfd - This function prints the characters from
  * the input string 'str'
  * to the specified file descriptor 'fd'.
  * @str: The string to be printed.
  * @fd: The file descriptor to write the characters to.
  *
  * Description: This function iterates through characters in input
  *string 'str'
  * calls '_putfd' function to write each character to file descriptor.
  * If the input string is empty or null, it returns 0.
  * Return: the total number of characters written to 'fd'.
  */
int _displaysfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _displayfd(*str++, fd);
	}
	return (i);
}
