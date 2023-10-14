#include "shell.h"
/**
  * _eputs - This function is responsible for displaying a given string.
  * @str: The input string to be printed.
  *
  * Description: function iterates through the chars in the input string 'str'
  * and calls another function '_eputchar' to print each char. If input string
  * is empty or null, it simply returns without doing anything
   */
void _eputs(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_eputchar(str[x]);
		x++;
	}
}
/**
  * _eputchar - function writes the character 'c' to the standard error stream.
  * @b: The character to be printed
  *
  * Description: function is designed to write a character 'c' to the standard
  * error stream (stderr). It utilizes an internal buffer 'buf' to store chars
  * before flushing them to stderr
  *Return: When the character 'c' is equal to BUF_FLUS
  * or the buffer is full, the contents of the buffer are written to stderr
  * On success, returns 1; on error, it returns -1 and sets errno appropriately
   */
int _eputchar(char b)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (b == FLUSH_BUFFER || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (b != FLUSH_BUFFER)
		buf[x++] = b;
	return (1);
}
/**
  * _putfd - This function writes the char 'c' to the file descriptor 'fd'.
  * @b: The character to be printed.
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
int _putfd(char b, int fd)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (b == FLUSH_BUFFER || x >= WRITE_BUF_SIZE)
	{
		write(fd, buf, x);
		x = 0;
	}
	if (b != FLUSH_BUFFER)
		buf[x++] = b;
	return (1);
}

/**
  * _putsfd - This function prints the characters from the input string 'str'
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
int _putsfd(char *str, int fd)
{
	int x = 0;

	if (!str)
		return (0);
	while (*str)
	{
		x += _putfd(*str++, fd);
	}
	return (x);
}
