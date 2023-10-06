#include "shell.h"

/**
 * find_node_index - locates the index of a specific node within a linked list
 * @list_head: pointer to the head of the linked list
 * @target_node: pointer to the node to find
 *
 * Return: the index of the target node or -1 if not found
 */
ssize_t find_node_index(list_t *list_head, list_t *target_node)
{
        size_t index = 0;

        while (list_head)
        {
        if (list_head == target_node)
                return (index);
        list_head = list_head->nextNode;
        index++;
        }
        return (-1);
}

/**
 * find_node_with_prefix - locate node whose string begins with given prefix
 * @c_node: pointer to the linked list's head
 * @prefix: string to search for as a prefix
 * @next_char: the character immediately following the prefix to match
 *
 * Return: the matching node or NULL if none found
 */
list_t *find_node_with_prefix(list_t *c_node, char *prefix, char next_char)
{
        char *matched_prefix = NULL;

        while (c_node)
        {
                matched_prefix = check_starts_with(c_node->stringValue, prefix);
                if (matched_prefix && ((next_char == -1) || (*matched_prefix == next_char)))
                        return (c_node);
                c_node = c_node->nextNode;
        }
        return (NULL);
}

/**
 * print_linked_list - prints all elements of a linked list
 * @head: pointer to the first node of the list
 *
 * Return: the number of elements in the list
 */
size_t print_linked_list(const list_t *head)
{
        size_t element_count = 0;

        while (head)
        {
        _puts(convert_to_string(head->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(head->stringValue ? head->stringValue : "(nil)");
        _puts("\n");
        head = head->nextNode;
        element_count++;
        }
        return (element_count);
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
        size_t list_size = get_list_length(head), j;
        char **string_array;
        char *str;

        if (!head || !list_size)
        return (NULL);

        string_array = malloc(sizeof(char *) * (list_size + 1));
        if (!string_array)
        return (NULL);

        for (list_size = 0; current_node; current_node = current_node->nextNode,
                        list_size++)
        {
                str = malloc(strlen(current_node->stringValue) + 1);
                if (!str)
                {
                        for (j = 0; j < list_size; j++)
                                free(string_array[j]);
                        free(string_array);
                        return (NULL);
                }
                str = _strcpy(str, current_node->stringValue);
                string_array[list_size] = str;
        }
        string_array[list_size] = NULL;
        return (string_array);
}

/**
 * get_list_length - calculates the size of a linked list
 * @head: pointer to the first node of the list
 *
 * Return: the number of elements in the list
 */
size_t get_list_length(const list_t *head)
{
        size_t count = 0;

        while (head)
        {
        head = head->nextNode;
        count++;
        }
        return (count);
}
