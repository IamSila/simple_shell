#include "main.h"


/**
 * swap_char - swaps | and & for non-printed chars
 *
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */


char *swap_char(char *input, int bool)
{
	int a;

	if (bool == 0)
	{
		for (a = 0; input[a]; a++)
		{
			if (input[a] == '|')
			{
				if (input[a + 1] != '|')
					input[a] = 16;
				else
					a++;
			}

			if (input[a] == '&')
			{
				if (input[a + 1] != '&')
					input[a] = 12;
else
					a++;
			}
		}
	}
	else
	{
		for (a = 0; input[a]; a++)
		{
			input[a] = (input[a] == 16 ? '|' : input[a]);
			input[a] = (input[a] == 12 ? '&' : input[a]);
		}
	}
	return (input);
}


/**
 * add_nodes - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input: input string
 *
 * Return: no return
 */


void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int a;
	char *my_line;

	input = swap_char(input, 0);

	for (a = 0; input[a]; a++)
	{
		if (input[a] == ';')
			add_sep_node_end(head_s, input[a]);

		if (input[a] == '|' || input[a] == '&')
		{
			add_sep_node_end(head_s, input[a]);
			a++;
		}
	}

	my_line = _strtok(input, ";|&");
	do {
		my_line = swap_char(my_line, 1);
		add_line_node_end(head_l, my_line);
		my_line = _strtok(NULL, ";|&");
	} while (my_line != NULL);

}

/**
 * go_next - goes to next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @datash: data structure
 *
 * Return: no return
 *
 */


void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_separator;
	sep_list *ls_start;
	line_list *ls_last;

	loop_separator = 1;
	ls_start = *list_s;
	ls_last = *list_l;

	while (ls_start != NULL && loop_separator)
	{
		if (datash->status == 0)
		{
			if (ls_start->separator == '&' || ls_start->separator == ';')
				loop_separator = 0;
			if (ls_start->separator == '|')
				ls_last = ls_last->next, ls_start = ls_start->next;
		}
		else
		{
			if (ls_start->separator == '|' || ls_start->separator == ';')
				loop_separator = 0;
			if (ls_start->separator == '&')
				ls_last = ls_last->next, ls_start = ls_start->next;
		}
		if (ls_start != NULL && !loop_separator)
			ls_start = ls_start->next;
	}

	*list_s = ls_start;
	*list_l = ls_last;
}



/**
 * split_commands - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @datash: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */


int split_commands(data_shell *datash, char *input)
{

	sep_list *head_start, *list_start;
	line_list *head_last, *list_last;
	int loop_counter;

	head_start = NULL;
	head_last = NULL;

	add_nodes(&head_start, &head_last, input);

	list_start = head_start;
	list_last = head_last;

	while (list_last != NULL)
	{
		datash->input = list_last->line;
		datash->args = split_line(datash->input);
		loop_counter = exec_line(datash);
		free(datash->args);

		if (loop_counter == 0)
			break;

		go_next(&list_start, &list_last, datash);

		if (list_last != NULL)
			list_last = list_last->next;
	}

	free_sep_list(&head_start);
	free_line_list(&head_last);

	if (loop_counter == 0)
		return (0);
	return (1);
}

/**
 * split_line - tokenizes the input string
 *
 * @input: input string.
 * Return: string splitted.
 *
 */


char **split_line(char *input)
{
	size_t buffer_size;
	size_t a;
	char **token_s;
	char *token;

	buffer_size = TOK_BUFSIZE;
	token_s = malloc(sizeof(char *) * (buffer_size));
	if (token_s == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	token_s[0] = token;

	for (a = 1; token != NULL; a++)
	{
		if (a == buffer_size)
		{
			buffer_size += TOK_BUFSIZE;
			token_s = _reallocdp(token_s, a, sizeof(char *) * buffer_size);
			if (token_s == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		token_s[a] = token;
	}

	return (token_s);
}
