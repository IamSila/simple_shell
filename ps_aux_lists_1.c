#include "main.h"

/**
 * add_sep_node_end - adds a separator found at the end
 * of a sep_list.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */

sep_list *add_sep_node_end(sep_list **head, char sep)
{
	sep_list *new, *tail;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	tail = *head;

	if (tail == NULL)
	{
		*head = new;
	}
	else
	{
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = new;
	}

	return (*head);
}

/**
 * free_sep_list - frees a sep_list
 * @head: head of the linked list.
 * Return: no return.
 */

void free_sep_list(sep_list **head)
{
	sep_list *tail;
	sep_list *current_list;

	if (head != NULL)
	{
		current_list = *head;
		while ((tail = current_list) != NULL)
		{
			current_list = current_list->next;
			free(tail);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end - adds a command line at the end
 * of a line_list.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *new, *tail;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	tail = *head;

	if (tail == NULL)
	{
		*head = new;
	}
	else
	{
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = new;
	}

	return (*head);
}

/**
 * free_line_list - frees a line_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_line_list(line_list **head)
{
	line_list *tail;
	line_list *current_list;

	if (head != NULL)
	{
		current_list = *head;
		while ((tail = current_list) != NULL)
		{
			current_list = current_list->next;
			free(tail);
		}
		*head = NULL;
	}
}
