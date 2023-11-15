#include "main.h"

/**
 * rev_string - fxn to reverse a string.
 * @s: the input string.
 *
 * Return: no return.
 */

void rev_string(char *s)
{
	int counter = 0, a, b;
	char *string, tail;

	while (counter >= 0)
	{
		if (s[counter] == '\0')
			break;
		counter++;
	}
	string = s;

	for (a = 0; a < (counter - 1); a++)
	{
		for (b = a + 1; b > 0; b--)
		{
			tail = *(string + b);
			*(string + b) = *(string + (b - 1));
			*(string + (b - 1)) = tail;
		}
	}
}
