#include "main.h"
/**
 * check_env - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 *
 * Return: there is no return value
 *
 */

void check_env(r_var **h, char *in, data_shell *data)
{
	int i, ch_row, j, last_value;
	char **_envr;

	_envr = data->_environ;
	for (i = 0; _envr[i]; i++)
	{
		for (j = 1, ch_row = 0; _envr[i][ch_row]; ch_row++)
		{
			if (_envr[i][ch_row] == '=')
			{
				last_value = _strlen(_envr[i] + ch_row + 1);
				add_rvar_node(h, j, _envr[i] + ch_row + 1, last_value);
				return;
			}

			if (in[j] == _envr[i][ch_row])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_rvar_node(h, j, NULL, 0);
}



/**
 * check_vars - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: there is no  return value
 */



int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int a, last_st, last_pd;

	last_st = _strlen(st);
	last_pd = _strlen(data->pid);

	for (a = 0; in[a]; a++)
	{
		if (in[a] == '$')
		{
			if (in[a + 1] == '?')
				add_rvar_node(h, 2, st, last_st), a++;
			else if (in[a + 1] == '$')
				add_rvar_node(h, 2, data->pid, last_pd), a++;
			else if (in[a + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[a + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[a + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[a + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[a + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + a, data);
		}
	}

	return (a);
}

/**
 * replaced_input - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 *
 */


char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int a, b, c;

	indx = *head;
	for (b = a = 0; a < nlen; a++)
	{
		if (input[b] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[a] = input[b];
				b++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (c = 0; c < indx->len_var; c++)
					b++;
				a--;
			}
			else
			{
				for (c = 0; c < indx->len_val; c++)
				{
					new_input[a] = indx->val[c];
					a++;
				}
				b += (indx->len_var);
				a--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[a] = input[b];
			b++;
		}
	}

	return (new_input);
}

/**
 * rep_var - calls functions to replace string into vars
 *
 * @input: is the input string
 * @datash: data structure
 * Return: return value is the replaced string
 */


char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int o_len, n_len;

	status = aux_itoa(datash->status);
	head = NULL;

	o_len = check_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	n_len = 0;

	while (indx != NULL)
	{
		n_len += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	n_len += o_len;

	new_input = malloc(sizeof(char) * (n_len + 1));
	new_input[n_len] = '\0';

	new_input = replaced_input(&head, input, new_input, n_len);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
