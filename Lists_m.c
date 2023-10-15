#include "shell.h"

/**
 * freeList - Frees all nodes in a linked list.
 * @headPtr: Address of the pointer to the head node.
 *
 * Return: void
 */
void freeList(list_t **headPtr)
{
	list_t *currentnode, *nextNode, *head;

	if (!headPtr || !*headPtr)
		return;
	head = *headPtr;
	currentnode = head;
	while (currentnode)
	{
		nextNode = currentnode->nextNode;
		free(currentnode->string);
		free(currentnode);
		currentnode = nextNode;
	}
	*headPtr = (NULL);
}

/**
 * deleteNodeAtIndex - Deletes a node at the specified index.
 * @head: Address of the pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int deleteNodeAtIndex(list_t **head, unsigned int index)
{
	list_t *currentnode, *prevNode;
	unsigned int x = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		currentnode = *head;
		*head = (*head)->nextNode;
		free(currentnode->string);
		free(currentnode);
		return (1);
	}
	currentnode = *head;
	while (currentnode)
	{
		if (x == index)
		{
			prevNode->nextNode = currentnode->nextNode;
			free(currentnode->string);
			free(currentnode);
			return (1);
		}
		x++;
		prevNode = currentnode;
		currentnode = currentnode->nextNode;
	}
	return (0);
}

/**
 * printStringList - Prints only the 'string' element of a list_t linked list.
 * @m: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t printStringList(const list_t *m)
{
	size_t x = 0;

	while (m)
	{
		_puts(m->string ? m->string : "(nil)");
		_puts("\n");
		m = m->nextNode;
		x++;
	}
	return (x);
}

/**
 * addNodeAtEnd - Appends a node to the end of the linked list.
 * @head: Address of the pointer to the head node.
 * @string: String field for the new node.
 * @number: Numeric index used for historical purposes.
 *
 * Return: The updated size of the list.
 */
list_t *addNodeAtEnd(list_t **head, const char *string, int number)
{
	list_t *newNode, *currentnode;

	if (!head)
	return (NULL);

	currentnode = *head;
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);
	memset((void *)newNode, 0, sizeof(list_t));
	newNode->number = number;
	if (string)
	{
		newNode->string = strdup(string);
		if (!newNode->string)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (currentnode)
	{
		while (currentnode->nextNode)
			currentnode = currentnode->nextNode;
		currentnode->nextNode = newNode;
	}
	else
		*head = newNode;
	return (newNode);
}

/**
 * addNode - Inserts a new node at the beginning of the linked list.
 * @head: Address of the pointer to the head node.
 * @string: String field for the new node.
 * @number: Numeric index used for historical purposes.
 *
 * Return: The updated size of the list.
 */
list_t *addNode(list_t **head, const char *string, int number)
{
	list_t *newNode;

	if (!head)
		return (NULL);

	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);

	memset((void *)newNode, 0, sizeof(list_t));
	newNode->number = number;
	if (string)
	{
		newNode->string = strdup(string);
		if (!newNode->string)
		{
			free(newNode);
			return (NULL);
		}
	}
	newNode->nextNode = *head;
	*head = newNode;
	return (newNode);
}
