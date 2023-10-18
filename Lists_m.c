#include "shell.h"

/**
 * release_list - releases all nodes in a linked list.
 * @head_ptr: location of the pointer to the head node.
 *
 * Return: return void
 */
void release_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

/**
 * remove_node_at_index - removess a node at the specified index.
 * @head: location of pointer to the 1st node.
 * @index: Index of the node to be removed
 *
 * Return: 1 when successful n 0 if not successful
 */
int remove_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}


/**
 * display_list_str - Prints the 'string' element of a list_t linked list.
 * @h: a pointer to the 1st node.
 *
 * Return: The dimensions of the list.
 */
size_t display_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * attach_node_end - Appends a node to the end of the linked list.
 * @head: Address of the pointer to the head node.
 * @str: String field for the new node.
 * @num: Numeric index used for historical purposes.
 *
 * Return: The updated size of the list.
 */
list_t *attach_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memoryset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strclone(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * attach_node - Inserts a new node at the beginning of the linked list.
 * @head: locations of the pointer to the head node.
 * @str: String field for the new node.
 * @num: Numeric index used for historical purposes.
 *
 * Return: The updated size of the list.
 */
list_t *attach_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memoryset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strclone(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}
