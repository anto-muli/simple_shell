#include "shell.h"
/**
 * _strcpy - Duplicates a string from source to destination.
 *
 * @desti: Pointer to the destination buffer
 * @srcs: Pointer to the source string
 * Return: Pointer to the destination buffer
 */
char *_strcpy(char *desti, char *srcs)
{
	int x = 0;

	if (desti == srcs || srcs == 0)
		return (desti);
	while (srcs[x])
	{
		desti[x] = srcs[x];
		x++;
	}
	desti[x] = 0;
	return (desti);
}
/**
 * _strdup - Duplicates a given string.
 *
 * @string: The string to be duplicated
 * Return: Pointer to the duplicated string
 */
char *_strdup(const char *string)
{
	int length = 0;
	char *turn;

	if (string == NULL)
		return (NULL);
	while (*string++)
		length++;
	turn = malloc(sizeof(char) * (length + 1));
	if (!turn)
		return (NULL);
	for (length++; length--;)
		turn[length] = *--string;
	return (turn);
}
/**
 * _puts - Prints a given string to the standard output.
 *
 * @string: The string to be printed
 * Return: None
 */
void _puts(char *string)
{
	int x = 0;

	if (!string)
		return;
	while (string[x] != '\0')
	{
		_putchar(string[x]);
		x++;
	}
}

/**
 * _putchar -  Writes the character 'c' to the standard output.
 *
 * @b: The character to be printed
 * Return: On success, returns 1. On error, returns -1
 * and sets the appropriate error code.
 */
int _putchar(char b)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (b == FLUSH_BUFFER || x >= WRITE_BUF_SIZE)
	{
		write(1, buf, x);
		x = 0;
	}
	if (b != FLUSH_BUFFER)
		buf[x++] = b;
	return (1);
}
