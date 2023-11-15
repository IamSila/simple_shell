#include "main.h"

/**
 * repeated_char - counts the repetitions of a char
 *
 * @input: input string
 * @i: index
 *
 * Return: repetitions
 */

int repeated_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, i + 1));

	return (i);
}

/**
 * error_sep_op - finds syntax errors
 *
 * @input: the input string
 * @i: an index
 * @last: last character read
 * Return: index of error. 0 when there are no
 * errors
 */

int error_sep_op(char *input, int i, char last)
{
	int counter;

	counter = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			counter = repeated_char(input, 0);
			if (counter == 0 || counter > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			counter = repeated_char(input, 0);
			if (counter == 0 || counter > 1)
				return (i);
		}
	}

	return (error_sep_op(input + 1, i + 1, *input));
}

/**
 * first_char - finds index of the first char
 *
 * @input: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */


int first_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - prints when a syntax error is found
 *
 * @datash: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 *
 * Return: no return
 */

void print_syntax_error(data_shell *datash, char *input, int i, int bool)
{
	char *message, *message2, *message3, *error, *counter;
	int len;

	if (input[i] == ';')
	{
		if (bool == 0)
			message = (input[i + 1] == ';' ? ";;" : ";");
		else
			message = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		message = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		message = (input[i + 1] == '&' ? "&&" : "&");

	message2 = ": Syntax error: \"";
	message3 = "\" unexpected\n";
	counter = aux_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(counter);
	len += _strlen(message) + _strlen(message2) + _strlen(message3) + 2;

	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, message2);
	_strcat(error, message);
	_strcat(error, message3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, len);
	free(error);
	free(counter);
}

/**
 * check_syntax_error - intermediate function to
 * find and print the syntax error
 *
 * @datash: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 if there is no error
 */

int check_syntax_error(data_shell *datash, char *input)
{
	int start = 0;
	int first_character = 0;
	int a = 0;

	first_character = first_char(input, &start);
	if (first_character == -1)
	{
		print_syntax_error(datash, input, start, 0);
		return (1);
	}

	a = error_sep_op(input + start, 0, *(input + start));
	if (a != 0)
	{
		print_syntax_error(datash, input, start + a, 1);
		return (1);
	}

	return (0);
}
