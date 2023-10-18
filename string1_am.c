#include "shell.h"
/**
 * _strcopy - Duplicates a string from source to destination.
 *
 * @dest: Pointer to the destination buffer
 * @src: Pointer to the source string
 * Return: Pointer to the destination buffer
 */
char *_strcopy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strclone - clones a specific strn
 *
 * @str: The specific strn to be cloned
 * Return: Pointer to the cloned string
 */
char *_strclone(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - Prints a given string to the standard output.
 *
 * @str: The string to be displayed
 * Return: no return value
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar -  outputs the chars 'c' to the standard output.
 *
 * @c: The char to be outputed
 * Return: when successful returns 1 n error, returns -1
 * and sets the appropriate error code.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
