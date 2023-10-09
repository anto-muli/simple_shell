#include "shell.h"
/**
  * strToIntWithErrHandling - Converts a string to an integer
  * @input_string: The input string to be converted
  * Return: The converted integer if successful,
  * 0 if no numbers in the string, or -1 on error
  */
int strToIntWithErrHandling(char *input_string)
{
	int index = 0;
	unsigned long int result = 0;

	if (*input_string == '+')
		input_string++; /* TODO: What is causing the main function to return a value of 255? */

	for (index = 0; input_string[index] != '\0'; index++)
	{
		if (input_string[index] >= '0' && input_string[index] <= '9')
		{
			result *= 10;
			result += (input_string[index] - '0');
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
  * print_error - Outputs an error message
  * @info: A struct containing parameter and return information
  * @error_string: A string specifying the type of error
  * Return: None
  */
void print_error(info_t *info, char *error_string)
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
  * @value: The integer value to be printed
  * @fd: The file descriptor to write to
  *
  * Return: The number of characters printed
  */
int print_decimal(int input, int fd)
{
	int (*output_char)(char) = _putchar;
	int i, character_count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		output_char = _putchar;
	if (value < 0)
	{
		absolute_value = -input;
		output_char('-');
		character_count++;
	}
	else
	{
		absolute_value = input;
	current = absolute_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			output_char('0' + current / i);
			character_count++;
		}
		current %= i;
	}
	output_char('0' + current);
	character_count++;
	return (character_count);
}
/**
  * convert_to_string - Converts a number to a string, similar to itoa
  * @number: The number to be converted
  * @base: The base for the conversion (e.g., decimal, hexadecimal)
  * @conversion_flags: Flags for customizing the conversion
  *
  * Return: A string representation of the converted number
   */
char *convert_to_string(long int number, int base, int conversion_flags)
{
	static char *base_characters;
	static char buffer[50];
	char sign = 0;
	char *pointer;
	unsigned long num = number;

	if (!(conversion_flags & CONVERT_UNSIGNED) && number < 0)
	{
		num = -number;
		sign = '-';
	}
	base_characters = conversion_flags & CONVERT_LOWERCASE ?
		"0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';
	do {
		*--pointer = base_characters[num % base];
		num /= base;
	} while (num != 0);
	if (sign)
		*--pointer = sign;
	return (pointer);
}


/**
  * remove_first_comment - Replaces the first instance of '#' with '\0'
  * @buf: The address of the string to modify
  *
  * Return: Always 0
  */
void remove_first_comment(char *buf)
{
	int index;

	for (index = 0; buf[index] != '\0'; index++)
	{
		if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
		{
			buf[index] = '\0';
			break;
		}
	}
}
