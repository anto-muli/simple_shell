#include "shell.h"

/**
 * bfree - deallocates memory pointed
 * to by a pointer and sets it to NULL
 *
 * @ptr: the location of the pointer to be freed
 *
 * Return: 1 if successfully freed n 0 if not
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
