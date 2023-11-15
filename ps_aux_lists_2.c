#include "main.h"

/**
 * add_rvar_node - adds a variable at the end
 * of a r_var list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval)
{
	r_var *new_one, *tail;

	new_one = malloc(sizeof(r_var));
	if (new_one == NULL)
		return (NULL);

	new_one->len_var = lvar;
	new_one->val = val;
	new_one->len_val = lval;

	new_one->next = NULL;
	tail = *head;

	if (tail == NULL)
	{
		*head = new_one;
	}
	else
	{
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = new_one;
	}

	return (*head);
}


/**
 * free_rvar_list - used to free a r_var list
 * @head: head of the linked list.
 *
 * Return: no return.
 */

void free_rvar_list(r_var **head)
{
	r_var *tail;
	r_var *current;

	if (head != NULL)
	{
		current = *head;
		while ((tail = current) != NULL)
		{
			current = current->next;
			free(tail);
		}
		*head = NULL;
	}
}
