#include "main.h"


/**
 * read_line - reads the input string.
 *
 * @i_eof: return value of getline function
 *
 * Return: should give an input string
 */


char *read_line(int *i_eof)
{
	char *input_x = NULL;
	size_t buffer_size = 0;

	*i_eof = getline(&input_x, &buffer_size, stdin);

	return (input_x);
}
