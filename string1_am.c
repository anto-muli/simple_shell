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
	int index = 0;

	if (desti == srcs || srcs == NULL)
		return (desti);
	while (srcs[index])
	{
		desti[index] = srcs[index];
		index++;
	}
	desti[index] = '\0';
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
	int index = 0;

	if (!strin)
		return;
	while (strin[index] != '\0')
	{
		_putchar(strin[index]);
		index++;
	}
}

/**
 * _putchar -  Writes the character 'c' to the standard output.
 *
 * @a: The character to be printed
 * Return: On success, returns 1. On error, returns -1
 * and sets the appropriate error code.
 */
int _putchar(char a)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (a == FLUSH_BUFFER || index >= WRITE_BUF_SIZE)
	{
		write(1, buf, index);
		index = 0;
	}
	if (a != FLUSH_BUFFER)
		buf[index++] = a;
	return (1);
}
