#include "main.h"


/**
 * without_comment - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */


char *without_comment(char *in)
{
	int j, counter;

	counter = 0;
	for (j = 0; in[j]; j++)
	{
		if (in[j] == '#')
		{
			if (j == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[j - 1] == ' ' || in[j - 1] == '\t' || in[j - 1] == ';')
				counter = j;
		}
	}

	if (counter != 0)
	{
		in = _realloc(in, j, counter + 1);
		in[counter] = '\0';
	}

	return (in);
}


/**
 * shell_loop - Loop of shell
 * @datash: data relevant (av, input, args)
 *
 * Return: no return value.
 */


void shell_loop(data_shell *datash)
{
	int loop_counter, i_eof;
	char *input_x;

	loop_counter = 1;
	while (loop_counter == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input_x = read_line(&i_eof);
		if (i_eof != -1)
		{
			input_x = without_comment(input_x);
			if (input_x == NULL)
				continue;

			if (check_syntax_error(datash, input_x) == 1)
			{
				datash->status = 2;
				free(input_x);
				continue;
			}
			input_x = rep_var(input_x, datash);
			loop_counter = split_commands(datash, input_x);
			datash->counter += 1;
			free(input_x);
		}
		else
		{
			loop_counter = 0;
			free(input_x);
		}
	}
}
