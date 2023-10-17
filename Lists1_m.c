#include "shell.h"

/**
 * fetch_node_index - locates the index of a specific node within a linked list
 * @head: pointer to the head of the linked list
 * @node: pointer to the node to find
 *
 * Return: the index of the target node or -1 if not found
 */
ssize_t fetch_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
/**
 * first_node - locate node whose string begins with given prefix
 * @node: pointer to the linked list's head
 * @prefix: string to search for as a prefix
 * @c: the character immediately following the prefix to match
 *
 * Return: the matching node or NULL if none found
 */
list_t *first_node(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = str_starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * print_list - prints all elements of a linked list
 * @h: pointer to the first node of the list
 *
 * Return: the number of elements in the list
 */
size_t display_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * convert_list_to_strings - creates array of strings from the list's str
 * @head: pointer to the first node of the list
 *
 * Return: an array of strings or NULL if empty or memory allocation fails
 */
char **convert_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlength(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * list_length - calculates the size of a linked list
 * @h: pointer to the first node of the list
 *
 * Return: the number of elements in the list
 */
size_t list_length(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}
