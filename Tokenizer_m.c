#include "shell.h"

/**
 * strtow - Splits an input string into words, ignoring repeated delimiters.
 * @str: The input string to be split.
 * @d: The delimiter string used for splitting.
 * Return: pointer to array of strings of words, or NULL on failure.
 */
char **strtow(char *str, char *d)
{
	int c_I, w_Index, charIndex, char_CIndex, numWords = 0;
	char **w_Array;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (c_I = 0; str[c_I] != '\0'; c_I++)
		if (!is_delim(str[c_I], d) && (is_delim(str[c_I + 1], d) || !str[c_I + 1]))
			numWords++;

	if (numWords == 0)
		return (NULL);
	w_Array = malloc((1 + numWords) * sizeof(char *));
	if (!w_Array)
		return (NULL);
	for (c_I = 0, w_Index = 0; w_Index < numWords; w_Index++)
	{
		while (is_delim(str[c_I], d))
			c_I++;
		charIndex = 0;
		while (!is_delim(str[c_I + charIndex], d) && str[c_I + charIndex])
			charIndex++;
		w_Array[w_Index] = malloc((charIndex + 1) * sizeof(char));
		if (!w_Array[w_Index])
		{
			for (charIndex = 0; charIndex < w_Index; charIndex++)
				free(w_Array[char_CIndex]);
			free(w_Array);
			return (NULL);
		}
		for (char_CIndex = 0; char_CIndex < c_I; char_CIndex++)
			w_Array[w_Index][char_CIndex] = str[c_I++];
		w_Array[w_Index][char_CIndex] = 0;
	}
	w_Array[w_Index] = NULL;
	return (w_Array);
}

/**
 * strtow2 - Splits an input string into words based on a specified delimiter.
 * @str: The input string to be split.
 * @d: The delimiter character used for splitting.
 * Return: A pointer to an array strings containing words, or NULL on failure.
 */

char **strtow2(char *str, char d)
{
	int c_Index, w_Index, charIndex, char_CIndex, numWords = 0;
	char **wordArray;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (c_Index = 0; str[c_Index] != '\0'; c_Index++)
		if ((str[c_Index] != d && str[c_Index + 1] == d) ||
			(str[c_Index] != d && !str[c_Index + 1]) || str[c_Index + 1] == d)
				numWords++;
	if (numWords == 0)
		return (NULL);
	wordArray = malloc((1 + numWords) * sizeof(char *));
	if (!wordArray)
		return (NULL);
	for (c_Index = 0, w_Index = 0; w_Index < numWords; w_Index++)
	{
		while (str[c_Index] == d && str[c_Index] != d)
			c_Index++;
		charIndex = 0;
		while (str[c_Index + charIndex] != d && str[c_Index + charIndex] &&
				str[c_Index + charIndex] != d)
			charIndex++;
		wordArray[w_Index] = malloc((charIndex + 1) * sizeof(char));
		if (!wordArray[w_Index])
		{
			for (char_CIndex = 0; char_CIndex < w_Index; char_CIndex++)
				free(wordArray[char_CIndex]);
			free(wordArray);
			return (NULL);
		}
		for (char_CIndex = 0; char_CIndex < charIndex; char_CIndex++)
			wordArray[w_Index][char_CIndex] = str[c_Index++];
		wordArray[w_Index][char_CIndex] = 0;
	}
	wordArray[w_Index] = NULL;
	return (wordArray);
}
