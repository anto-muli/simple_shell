#include "shell.h"
/**
 * _strncopy - Copies a substring of a source string to a destination string.
 * @dest: Pointer to the destination string where the copy is made.
 * @src: Pointer to the source string to be copied from.
 * @n: The maximum number of characters to be copied,
 * including the null terminator.
 * Return: Pointer to the destination string
 */

char *_strncopy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
  * _strnconcatenate - Concatenates two strings, limiting the number of bytes used.
  * @dest: The first string to which the second string is concatenated.
  * @src: The second string to be concatenated.
  * @n: The maximum number of bytes to be used from the source string.
  * Return: Pointer to the concatenated string.
  */
char *_strnconcatenate(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
  * _strchars - Locates the first occurrence of a character in a string.
  * @s: The string in which the character is searched.
  * @c: The character to find in the string.
  * Return: A pointer to the first occurrence of 'c' in 's',
  * or NULL if not found.
  */
char *_strchars(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
