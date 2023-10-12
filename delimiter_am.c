#include "shell.h"
/**
 * interactive - Check if the shell is in interactive mode.
 * This function checks whether the shell is running in interactive mode.
 *
 * @info: Pointer to a structure containing shell information.
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checks for  delimiters in a char
 *
 * This function checks if a given character is a
 * delimiter by comparing it to a delimiter string.
 *
 * @x: The character to check
 * @delim: The delimiter string.
 *
 * Return: 1 if the character x is a delimiter, 0 otherwise.
 */

int is_delim(char x, char *delim)
{
	while (*delim)
		if (*delim++ == x)
			return (1);
	return (0);
}

/**
 * _isalpha - Check if a character is alphabetic.
 * This function checks if a given character is an
 * alphabetic character (letter).
 *
 * @x: The character to check.
 *
 * Return: 1 if the character x is an alphhabet, 0 otherwise.
 */
int _isalpha(int x)
{
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi -  Convert a string to an int
 * This function takes a string as input and
 * attempts to convert it to an integer
 * @a: The converted string
 * Return: The converted integer if successful;
 * otherwise, 0 if no numbers are found in the string.
 */
int _atoi(char *a)
{
	int b, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (b = 0; a[b] != '\0' && flag != 2; b++)
	{
		if (a[b] == '-')
			sign *= -1;

		if (a[b] >= '0' && a[b] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (a[b] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
