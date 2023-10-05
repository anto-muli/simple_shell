#include "shell.h"
/**
 * _strncpy - Copies a substring of a source string to a destination string.
 * @dest: Pointer to the destination string where the copy is made.
 * @src: Pointer to the source string to be copied from.
 * @x: The maximum number of characters to be copied,
 * including the null terminator.
 * Return: Pointer to the destination string
 */

char *_strncpy(char *dest, char *src, int x)
{
	int source_index, dest_index;
	char *result = dest;

	source_index = 0;
	while (src[source_index] != '\0' && source_index < x - 1)
	{
		dest[source_index] = src[source_index];
		source_index++;
	}
	if (source_index < x)
	{
		dest_index = source_index;
		while (dest_index < x)
		{
			dest[dest_index] = '\0';
			dest_index++;
		}
	}
	return (result);
}
/**
  * _strncat - Concatenates two strings, limiting the number of bytes used.
  * @dest: The first string to which the second string is concatenated.
  * @src: The second string to be concatenated.
  * @x: The maximum number of bytes to be used from the source string.
  * Return: Pointer to the concatenated string.
  */
char *_strncat(char *dest, char *src, int x)
{
	int dest_index, src_index;
	char *result = dest;

	dest_index = 0;
	while (dest[dest_index] != '\0')
	{
		dest_index++;
	}
	src_index = 0;
	while (src[src_index] != '\0' && src_index < x)
	{
		dest[dest_index] = src[src_index];
		dest_index++;
		src_index++;
	}
	if (src_index < x)
	{
		dest[dest_index] = '\0';
	}
	return (result);
}


/**
  * _strchr - Locates the first occurrence of a character in a string.
  * @a: The string in which the character is searched.
  * @b: The character to find in the string.
  * Return: A pointer to the first occurrence of 'c' in 's',
  * or NULL if not found.
  */
char *_strchr(char *a, char b)
{
	do {
		if (*a == b)
			return (a);
	} while (*a++ != '\0');
	return (NULL);
}

