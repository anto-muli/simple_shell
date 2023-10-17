#include "shell.h"
/**
  * _erratoi - will convert a string to an integer
  * @s: The input string to be converted
  * Return: The converted integer if successful,
  * 0 if no numbers in the string, or -1 on error
  */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: what causes the main function to return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
  * display_error - Outputs an error message
  * @info: A struct containing parameter and return information
  * @estr: A string specifying the type of error
  * Return: None
  */
void display_error(info_t *info, char *estr)
{
	_displaystr(info->fname);
	_displaystr(": ");
	display_d(info->line_count, STDERR_FILENO);
	_displaystr(": ");
	_displaystr(info->argv[0]);
	_displaystr(": ");
	_displaystr(estr);
}

/**
  * display_d - Prints an integer (decimal number in base 10)
  * @input: The integer value to be printed
  * @fd: The file descriptor to write to
  *
  * Return: The number of characters printed
  */
int display_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _displaychar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;
	return (count);
}

/**
  * change_number - Converts a number to a string, similar to itoa
  * @num: The number to be converted
  * @base: The base for the conversion (e.g., decimal, hexadecimal)
  * @flags: Flags for customizing the conversion
  *
  * Return: A string representation of the converted number
  */
char *change_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
  * eliminate_comments - it replaces the first instance of '#' with '\0'
  * @buf: The address of the string to be modified
  *
  * Return: Always 0
  */
void eliminate_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
