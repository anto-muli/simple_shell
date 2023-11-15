#include "shell.h"

/**
 * find_node_index - locates the index of a specific node within a linked list
 * @head: pointer to the head of the linked list
 * @target_node: pointer to the node to find
 *
 * Return: the index of the target node or -1 if not found
 */
ssize_t find_node_index(list_t *head, list_t *target_node)
{
	size_t x = 0;

	while (head)
	{
		if (head == target_node)
			return (x);
		head = head->nextNode;
		x++;
	}
	return (-1);
}
/**
 * find_node_with_prefix - locate node whose string begins with given prefix
 * @c_node: pointer to the linked list's head
 * @prefix: string to search for as a prefix
 * @b: the character immediately following the prefix to match
 *
 * Return: the matching node or NULL if none found
 */
list_t *find_node_with_prefix(list_t *c_node, char *prefix, char b)
{
	char *t = NULL;

	while (c_node)
	{
		t = check_starts_with(c_node->stringValue, prefix);
		if (t && ((b == -1) || (*t == b)))
			return (c_node);
		c_node = c_node->nextNode;
	}
	return (NULL);
}

/**
 * print_linked_list - prints all elements of a linked list
 * @m: pointer to the first node of the list
 *
 * Return: the number of elements in the list
 */
size_t print_linked_list(const list_t *m)
{
	size_t x = 0;

	while (m)
	{
		_puts(convert_number(m->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(m->stringValue ? m->stringValue : "(nil)");
		_puts("\n");
		m = m->nextNode;
		x++;
	}
	return (x);
}

/**
 * convert_list_to_strings - creates array of strings from the list's str
 * @head: pointer to the first node of the list
 *
 * Return: an array of strings or NULL if empty or memory allocation fails
 */
char **convert_list_to_strings(list_t *head)
{
	list_t *current_node = head;
	size_t x = get_list_length(head), k;
	char **string_array;
	char *str;

	if (!head || !x)
		return (NULL);
	string_array = malloc(sizeof(char *) * (x + 1));
	if (!string_array)
		return (NULL);
	for (x = 0; current_node; current_node = current_node->nextNode,
			x++)
	{
		str = malloc(_strlen(current_node->stringValue) + 1);
		if (!str)
		{
			for (k = 0; k < x; k++)
				free(string_array[k]);
			free(string_array);
			return (NULL);
		}
		str = _strcpy(str, current_node->stringValue);
		string_array[x] = str;
	}
	string_array[x] = NULL;
	return (string_array);
}

/**
 * get_list_length - calculates the size of a linked list
 * @m: pointer to the first node of the list
 *
 * Return: the number of elements in the list
 */
size_t get_list_length(const list_t *m)
{
	size_t x = 0;

	while (m)
	{
		m = m->nextNode;
		x++;
	}
	return (x);
}
