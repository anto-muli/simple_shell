#include "shell.h"

/**
 * _realloc - Function Reallocates a block of memory.
 * @ptr: Pointer to the previously allocated memory block.
 * @old_size: Size of the previous memory block in bytes.
 * @new_size: Size of the new memory block in bytes.
 *
 * Return: Pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
 * ffree - Function frees an array of strings.
 * @pp: Pointer to the array of strings.
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * *_memset - Function fills a memory block with a constant byte.
 * @s: Pointer to the memory block.
 * @b: Byte value to fill the memory block with.
 * @n: Number of bytes to fill in the memory block.
 * Return: Pointer to the modified memory block (dest).
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

