#include "shell.h"

/**
 * freeList - Frees all nodes in a linked list.
 * @headPtr: Address of the pointer to the head node.
 *
 * Return: void
 */
void freeList(list_t **headPtr)
{
        list_t *currentNode, *nextNode, *head;

        if (!headPtr || !*headPtr)
        return;

        head = *headPtr;
        currentNode = head;

        while (currentNode)
        {
        nextNode = currentNode->nextNode;
        free(currentNode->stringValue);
        free(currentNode);
        currentNode = nextNode;
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
        list_t *currentNode, *prevNode;
        unsigned int currentIndex = 0;

        if (!head || !*head)
        return (0);

        if (!index)
        {
        currentNode = *head;
        *head = (*head)->nextNode;
        free(currentNode->stringValue);
        free(currentNode);
        return (1);
        }

        currentNode = *head;
        while (currentNode)
        {
        if (currentIndex == index)
        {
                prevNode->nextNode = currentNode->nextNode;
                free(currentNode->stringValue);
                free(currentNode);
                return (1);
        }
        currentIndex++;
        prevNode = currentNode;
        currentNode = currentNode->nextNode;
        }

        return (0);
}

/**
 * printStringList - Prints only the 'str' element of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t printStringList(const list_t *h)
{
        size_t count = 0;

        while (h)
        {
        _puts(h->stringValue ? h->stringValue : "(nil)");
        _puts("\n");
        h = h->nextNode;
        count++;
        }

        return (count);
}

/**
 * addNodeAtEnd - Appends a node to the end of the linked list.
 * @head: Address of the pointer to the head node.
 * @str: String field for the new node.
 * @num: Numeric index used for historical purposes.
 *
 * Return: The updated size of the list.
 */
list_t *addNodeAtEnd(list_t **head, const char *str, int num)
{
        list_t *newNode, *currentNode;

        if (!head)
        return (NULL);

        newNode = malloc(sizeof(list_t));
        if (!newNode)
        return (NULL);
        memset((void *)newNode, 0, sizeof(list_t));
        newNode->num = num;

        if (str)
        {
        newNode->stringValue = strdup(str);
        if (!newNode->stringValue)
        {
                free(newNode);
                return (NULL);
        }
        }

        currentNode = *head;
        if (currentNode)
        {
        while (currentNode->nextNode)
                currentNode = currentNode->nextNode;
        currentNode->nextNode = newNode;
        }
        else
        {
        *head = newNode;
        }

        return (newNode);
}

/**
 * addNode - Inserts a new node at the beginning of the linked list.
 * @head: Address of the pointer to the head node.
 * @str: String field for the new node.
 * @num: Numeric index used for historical purposes.
 *
 * Return: The updated size of the list.
 */
list_t *addNode(list_t **head, const char *str, int num)
{
        list_t *newNode;

        if (!head)
        return (NULL);

        newNode = malloc(sizeof(list_t));
        if (!newNode)
        return (NULL);

        memset((void *)newNode, 0, sizeof(list_t));

        newNode->num = num;

        if (str)
        {
        newNode->stringValue = strdup(str);
        if (!newNode->stringValue)
        {
                free(newNode);
                return (NULL);
        }
        }

        newNode->nextNode = *head;

        *head = newNode;

        return (newNode);
}
