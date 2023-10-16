#include "shell.h"

/**
 * _strcat - Combines two strings source to destinatiom.
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source buffer.
 *
 * Return: A pointer to the destination buffer after the concatenation.
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * starts_with - Determines haystack string begins needle substring.
 * @haystack: The string to search within.
 * @needle: The substring to look for at the start of the haystack.
 *
 * Return: A pointer to the next character in the haystack after the needle,
 *          or NULL if the haystack does not start with the needle.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcmp - Compares two strings lexicographically.
 * @s1: Pointer to the first string.
 * @s2: Pointer to the second string.
 *
 * Return: A negative value if str1 comes before str2, a positive value if
 *          str1 comes after str2, and zero if str1 is equal to str2.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _strlen - Computes the length of a given string.
 * @s: Pointer to the string whose length is to be determined.
 *
 * Return: An integer representing the length of the string.
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}
