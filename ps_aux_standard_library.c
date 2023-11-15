#include "main.h"

/**
 * get_len - Get the lenght of a number.
 * @n: type int number.
 * Return: Lenght of a number.
 */

int get_len(int n)
{
	unsigned int n_1;
	int len = 1;

	if (n < 0)
	{
		len++;
		n_1 = n * -1;
	}
	else
	{
		n_1 = n;
	}
	while (n_1 > 9)
	{
		len++;
		n_1 = n_1 / 10;
	}

	return (len);
}


/**
 * aux_itoa - function converts int to string.
 * @n: type int number
 * Return: String.
 */


char *aux_itoa(int n)
{
	unsigned int n_1;
	int len = get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + len) = '\0';

	if (n < 0)
	{
		n_1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n_1 = n;
	}

	len--;
	do {
		*(buffer + len) = (n_1 % 10) + '0';
		n_1 = n_1 / 10;
		len--;
	}
	while (n_1 > 0)
		;
	return (buffer);
}


/**
 * _atoi - converts a string to an integer.
 * @s: input string.
 *
 * Return: returns an integer.
 */


int _atoi(char *s)
{
	unsigned int counter = 0, size = 0, o_i = 0, p_number = 1, i = 1, j;

	while (*(s + counter) != '\0')
	{
		if (size > 0 && (*(s + counter) < '0' || *(s + counter) > '9'))
			break;

		if (*(s + counter) == '-')
			p_number *= -1;

		if ((*(s + counter) >= '0') && (*(s + counter) <= '9'))
		{
			if (size > 0)
				i *= 10;
			size++;
		}
		counter++;
	}

	for (j = counter - size; j < counter; j++)
	{
		o_i = o_i + ((*(s + j) - 48) * i);
		i /= 10;
	}
	return (o_i * p_number);
}
