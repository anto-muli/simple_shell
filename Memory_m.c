#include "shell.h"

/**
 * safely_free_pointer - deallocates memory pointed
 * to by a pointer and sets it to NULL
 *
 * @pt: address of the pointer to be freed
 *
 * Return: 1 if successfully freed, otherwise 0.
 */
int safely_free_pointer(void **pt)
{
	if (pt && *pt)
	{
		free(*pt);
		*pt = NULL;
		return (1);
	}
	return (0);
}
