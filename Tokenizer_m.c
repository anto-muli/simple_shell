#include "shell.h"

/**
 * strtow - Splits an input string into words, ignoring repeated delimiters.
 * @string: The input string to be split.
 * @d: The delimiter string used for splitting.
 * Return: pointer to array of strings of words, or NULL on failure.
 */
char **strtow(char *string, char *d)
{
	int x, k, l, n, numWords = 0;
	char **y;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (x = 0; string[x] != '\0'; x++)
		if (!is_delim(string[x], d) && (is_delim(string[x + 1], d) || !string[x + 1]))
			numWords++;

	if (numWords == 0)
		return (NULL);
	y = malloc((1 + numWords) * sizeof(char *));
	if (!y)
		return (NULL);
	for (x = 0, k = 0; k < numWords; k++)
	{
		while (is_delim(string[x], d))
			x++;
		l = 0;
		while (!is_delim(string[x + l], d) && string[x + l])
			l++;
		y[k] = malloc((l + 1) * sizeof(char));
		if (!y[k])
		{
			for (l = 0; l < k; l++)
				free(y[n]);
			free(y);
			return (NULL);
		}
		for (n = 0; n < x; n++)
			y[k][n] = string[x++];
		y[k][n] = 0;
	}
	y[k] = NULL;
	return (y);
}

/**
 * strtow2 - Splits an input string into words based on a specified delimiter.
 * @string: The input string to be split.
 * @c: The delimiter character used for splitting.
 * Return: A pointer to an array strings containing words, or NULL on failure.
 */

char **strtow2(char *string, char c)
{
	int x, k, l, n, numWords = 0;
	char **y;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (x = 0; string[x] != '\0'; x++)
		if ((string[x] != c && string[x + 1] == c) ||
				(string[x] != c && !string[x + 1]) || string[x + 1] == c)
			numWords++;
	if (numWords == 0)
		return (NULL);
	y = malloc((1 + numWords) * sizeof(char *));
	if (!y)
		return (NULL);
	for (x = 0, k = 0; k < numWords; k++)
	{
		while (string[x] == c && string[x] != c)
			x++;
		l = 0;
		while (string[x + l] != c && string[x + l] &&
				string[x + l] != c)
			l++;
		y[k] = malloc((l + 1) * sizeof(char));
		if (!y[k])
		{
			for (n = 0; n < k; n++)
				free(y[n]);
			free(y);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			y[k][n] = string[x++];
		y[k][n] = 0;
	}
	y[k] = NULL;
	return (y);
}
