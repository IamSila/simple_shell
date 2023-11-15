#include "main.h"

/**
 * bring_line - assigns the line var for get_line
 * @lineptr: Buffer that store the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */

void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * get_line - Read inpt from stream
 * @lineptr: buffer that stores the input
 * @n: size of line pointer
 * @stream: the stream to read from
 * Return: It will return the number of bytes
 */

ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int a;
	static ssize_t input_x;
	ssize_t retval;
	char *buffer;
	char p = 'z';

	if (input_x == 0)
		fflush(stream);
	else
		return (-1);
	input_x = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (p != '\n')
	{
		a = read(STDIN_FILENO, &p, 1);
		if (a == -1 || (a == 0 && input_x == 0))
		{
			free(buffer);
			return (-1);
		}
		if (a == 0 && input_x != 0)
		{
			input_x++;
			break;
		}
		if (input_x >= BUFSIZE)
			buffer = _realloc(buffer, input_x, input_x + 1);
		buffer[input_x] = p;
		input_x++;
	}
	buffer[input_x] = '\0';
	bring_line(lineptr, n, buffer, input_x);
	retval = input_x;
	if (a != 0)
		input_x = 0;
	return (retval);
}
