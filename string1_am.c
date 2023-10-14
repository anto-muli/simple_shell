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
 * @strin: The string to be duplicated
 * Return: Pointer to the duplicated string
 */
char *_strdup(const char *strin)
{
	int str_length = 0;
	char *duplicate_str;

	if (strin == NULL)
		return (NULL);
	while (*strin++)
		str_length++;
	duplicate_str = malloc(sizeof(char) * (str_length + 1));
	if (!duplicate_str)
		return (NULL);
	for (str_length++; str_length--;)
		duplicate_str[str_length] = *--strin;
	return (duplicate_str);
}
/**
 * _puts - Prints a given string to the standard output.
 *
 * @strin: The string to be printed
 * Return: None
 */
void _puts(char *strin)
{
	int x = 0;

	if (!strin)
		return;
	while (strin[x] != '\0')
	{
		_putchar(strin[x]);
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
