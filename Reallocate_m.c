#include "shell.h"

/**
 * customReallocate - Function Reallocates a block of memory.
 * @pointer: Pointer to the previously allocated memory block.
 * @oldSize: Size of the previous memory block in bytes.
 * @newSize: Size of the new memory block in bytes.
 *
 * Return: Pointer to the reallocated memory block.
 */
void *customReallocate(void *pointer, unsigned int oldSize, unsigned int newSize)
{
        char *newPtr;

        if (!pointer)
        return (malloc(newSize));

        if (!newSize)
        {
        free(pointer);
        return (NULL);
        }

        if (newSize == oldSize)
        return (pointer);

        newPtr = malloc(newSize);
        if (!newPtr)
        return (NULL);

        oldSize = oldSize < newSize ? oldSize : newSize;
        while (oldSize--)
        newPtr[oldSize] = ((char *)pointer)[oldSize];

        free(pointer);
        return (newPtr);
}

/**
 * freeStringArray - Function frees an array of strings.
 * @strArray: Pointer to the array of strings.
 */
void freeStringArray(char **strArray)
{
        char **tempArray = strArray;

        if (!strArray)
                return;

        while (*strArray)
        free(*strArray++);

        free(tempArray);
}

/**
 * my_memset - Function fills a memory block with a constant byte.
 * @dest: Pointer to the memory block.
 * @byte: Byte value to fill the memory block with.
 * @size: Number of bytes to fill in the memory block.
 * Return: Pointer to the modified memory block (dest).
 */
char *my_memset(char *dest, char byte, unsigned int size)
{
        unsigned int index;

        for (index = 0; index < size; index++)
        dest[index] = byte;

        return (dest);
}
