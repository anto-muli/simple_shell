#include "shell.h"

/**
 * customReallocate - Function Reallocates a block of memory.
 * @pt: Pointer to the previously allocated memory block.
 * @oldSize: Size of the previous memory block in bytes.
 * @newSize: Size of the new memory block in bytes.
 *
 * Return: Pointer to the reallocated memory block.
 */
void *customReallocate(void *pt, unsigned int oldSize, unsigned int newSize)
{
	char *t;

	if (!pt)
		return (malloc(newSize));
	if (!newSize)
		return (free(pt), NULL);
	if (newSize == oldSize)
		return (pt);

	t = malloc(newSize);
	if (!t)
		return (NULL);

	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		t[oldSize] = ((char *)pt)[oldSize];

	free(pt);
	return (t);
}

/**
 * freeStringArray - Function frees an array of strings.
 * @tt: Pointer to the array of strings.
 */
void freeStringArray(char **tt)
{
	char **z = tt;

	if (!tt)
		return;

	while (*tt)
		free(*tt++);

	free(z);
}

/**
 * my_memset - Function fills a memory block with a constant byte.
 * @y: Pointer to the memory block.
 * @a: Byte value to fill the memory block with.
 * @q: Number of bytes to fill in the memory block.
 * Return: Pointer to the modified memory block (dest).
 */
char *my_memset(char *y, char a, unsigned int q)
{
	unsigned int x;

	for (x = 0; x < q; x++)
		y[x] = a;

	return (y);
}
