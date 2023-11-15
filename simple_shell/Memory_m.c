#include "shell.h"

/**
 * safely_free_pointer - deallocates memory pointed
 * to by a pointer and sets it to NULL
 *
 * @pointer: address of the pointer to be freed
 *
 * Return: 1 if successfully freed, otherwise 0.
 */
int safely_free_pointer(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
