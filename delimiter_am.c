#include "shell.h"
/**
 * is_interactive - Check if the shell is in interactive mode.
 * This function checks whether the shell is running in interactive mode.
 *
 * @info: Pointer to a structure containing shell information.
 *
 * Return: 1 if the shell is in interactive mode, 0 if not
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * check_delim - Checks for  delimiters in a char
 *
 * This function checks if a given character is a
 * delimiter by comparing it to a delimiter string.
 *
 * @c: The character to check
 * @delim: The delimiter string.
 *
 * Return: 1 if the character x is a delimiter, 0 if not
 */

int check_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _checkalpha - Check if a character is alphabetic.
 * This function checks if a given character is an
 * alphabetic character (letter).
 *
 * @c: The character to check.
 *
 * Return: 1 if the character x is an alphhabet, 0 otherwise.
 */
int _checkalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	else
		return (0);
}

/**
 * _atomizer -  Convert a string to an int
 * This function takes a string as input and
 * attempts to convert it to an integer
 * @s: The converted string
 * Return: The converted integer if successful;
 * otherwise, 0 if no numbers are found in the string.
 */
int _atomizer(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
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
