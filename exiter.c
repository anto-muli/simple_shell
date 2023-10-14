#include "shell.h"
/**
 * _strncpy - Copies a substring of a source string to a destination string.
 * @dest: Pointer to the destination string where the copy is made.
 * @src: Pointer to the source string to be copied from.
 * @q: The maximum number of characters to be copied,
 * including the null terminator.
 * Return: Pointer to the destination string
 */

char *_strncpy(char *dest, char *src, int q)
{
	int x, k;
	char *y = dest;

	x = 0;
	while (src[x] != '\0' && x < q - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < q)
	{
		k = x;
		while (k < q)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (y);
}
/**
  * _strncat - Concatenates two strings, limiting the number of bytes used.
  * @dest: The first string to which the second string is concatenated.
  * @src: The second string to be concatenated.
  * @q: The maximum number of bytes to be used from the source string.
  * Return: Pointer to the concatenated string.
  */
char *_strncat(char *dest, char *src, int q)
{
	int x, k;
	char *y = dest;

	x = 0;
	while (dest[x] != '\0')
	{
		x++;
	}
	k = 0;
	while (src[k] != '\0' && k < q)
	{
		dest[x] = src[k];
		x++;
		k++;
	}
	if (k < q)
	{
		dest[x] = '\0';
	}
	return (y);
}


/**
  * my_strchr - Locates the first occurrence of a character in a string.
  * @y: The string in which the character is searched.
  * @a: The character to find in the string.
  * Return: A pointer to the first occurrence of 'c' in 's',
  * or NULL if not found.
  */
char *my_strchr(char *y, char a)
{
	do {
		if (*y == a)
			return (y);
	} while (*y++ != '\0');
	return (NULL);
}
