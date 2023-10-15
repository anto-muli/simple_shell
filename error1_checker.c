#include "shell.h"
/**
  * strToIntWithErrHandling - will convert a string to an integer
  * @y: The input string to be converted
  * Return: The converted integer if successful,
  * 0 if no numbers in the string, or -1 on error
  */
int strToIntWithErrHandling(char *y)
{
	int x = 0;
	unsigned long int result = 0;

	if (*y == '+')
		y++; /* TODO: What is causing the main function to return a value of 255? */

	for (x = 0; y[x] != '\0'; x++)
	{
		if (y[x] >= '0' && y[x] <= '9')
		{
			result *= 10;
			result += (y[x] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
		{
			return (-1);
		}
	}
	return (result);
}

/**
  * displayErrorMessage - Outputs an error message
  * @info: A struct containing parameter and return information
  * @error_string: A string specifying the type of error
  * Return: None
  */
void displayErrorMessage(info_t *info, char *error_string)
{
	_eputs(info->fname);
	_eputs(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_string);
}

/**
  * print_decimal - Prints an integer (decimal number in base 10)
  * @input: The integer value to be printed
  * @fd: The file descriptor to write to
  *
  * Return: The number of characters printed
  */
int print_decimal(int input, int fd)
{
	int (*_putchar)(char) = _putchar;
	int x, character_count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		_putchar = _eputchar;
	if (input < 0)
	{
		absolute_value = -input;
		_putchar('-');
		character_count++;
	}
	else
	{
		absolute_value = input;
	current = absolute_value;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (absolute_value / x)
		{
			_putchar('0' + current / x);
			character_count++;
		}
		current %= x;
	}
	_putchar('0' + current);
	character_count++;
	return (character_count);
}

/**
  * convert_number - Converts a number to a string, similar to itoa
  * @number: The number to be converted
  * @base: The base for the conversion (e.g., decimal, hexadecimal)
  * @flags: Flags for customizing the conversion
  *
  * Return: A string representation of the converted number
  */
char *convert_number(long int number, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *pt;
	unsigned long q = number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		q = -number;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ?
		"0123456789abcdef" : "0123456789ABCDEF";
	pt = &buffer[49];
	*pt = '\0';
	do {
		*--pt = array[q % base];
		q /= base;
	} while (q != 0);
	if (sign)
		*--pt = sign;
	return (pt);
}


/**
  * remove_comments - it replaces the first instance of '#' with '\0'
  * @buf: The address of the string to be modified
  *
  * Return: Always 0
  */
void remove_comments(char *buf)
{
	int x;

	for (x = 0; buf[x] != '\0'; x++)
		if (buf[x] == '#' && (!x || buf[x - 1] == ' '))
		{
			buf[x] = '\0';
			break;
		}
}
