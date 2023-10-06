#include "shell.h"

/**
 * concatenate_strings - Combines two strings source to destinatiom.
 * @destination: Pointer to the destination buffer.
 * @source: Pointer to the source buffer.
 *
 * Return: A pointer to the destination buffer after the concatenation.
 */
char *concatenate_strings(char *destination, char *source)
{
        char *result = destination;

        while (*destination)
        destination++;

        while (*source)
        *destination++ = *source++;

        *destination = *source;
        return (result);
}

/**
 * check_starts_with - Determines haystack string begins needle substring.
 * @haystack: The string to search within.
 * @needle: The substring to look for at the start of the haystack.
 *
 * Return: A pointer to the next character in the haystack after the needle,
 *          or NULL if the haystack does not start with the needle.
 */
char *check_starts_with(const char *haystack, const char *needle)
{
        while (*needle)
        {
        if (*needle++ != *haystack++)
                return (NULL);
        }
        return ((char *)haystack);
}

/**
 * compare_strings - Compares two strings lexicographically.
 * @str1: Pointer to the first string.
 * @str2: Pointer to the second string.
 *
 * Return: A negative value if str1 comes before str2, a positive value if
 *          str1 comes after str2, and zero if str1 is equal to str2.
 */
int compare_strings(char *str1, char *str2)
{
        while (*str1 && *str2)
        {
        if (*str1 != *str2)
                return (*str1 - *str2);
        str1++;
        str2++;
        }

        if (*str1 == *str2)
        return (0);
        else
        return (*str1 < *str2 ? -1 : 1);
}

/**
 * get_string_length - Computes the length of a given string.
 * @str: Pointer to the string whose length is to be determined.
 *
 * Return: An integer representing the length of the string.
 */
int get_string_length(char *str)
{
        int length = 0;

        if (!str)
        return (0);

        while (*str++)
        length++;

        return (length);
}
