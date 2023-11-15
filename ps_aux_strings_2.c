#include "main.h"

/**
 * _strdup - duplicates a str in the heap memory.
 * @s: Type character pointer string
 *
 * Return: duplicated str
 */

char *_strdup(const char *s)
{
	char *new_string;
	size_t length;

	length = _strlen(s);
	new_string = malloc(sizeof(char) * (length + 1));
	if (new_string == NULL)
		return (NULL);
	_memcpy(new_string, s, length + 1);
	return (new_string);
}

/**
 * _strlen - Returns the length of a string.
 * @s: Type char pointer
 *
 * Return: Always 0.
 */

int _strlen(const char *s)
{
	int length;

	for (length = 0; s[length] != 0; length++)
	{
	}
	return (length);
}

/**
 * cmp_chars - compares the characters in a string
 * @str: the input string.
 * @delim: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */

int cmp_chars(char str[], const char *delim)
{
	unsigned int a, b, l;

	for (a = 0, l = 0; str[a]; a++)
	{
		for (b = 0; delim[b]; b++)
		{
			if (str[a] == delim[b])
			{
				l++;
				break;
			}
		}
	}
	if (a == l)
		return (1);
	return (0);
}

/**
 * _strtok - splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */

char *_strtok(char str[], const char *delim)
{
	static char *splitted_str, *string_end;
	char *string_start;
	unsigned int a, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted_str = str; /*Store first address*/
		a = _strlen(str);
		string_end = &str[a]; /*Store last address*/
	}
	string_start = splitted_str;
	if (string_start == string_end) /*Reaching the end*/
		return (NULL);

	for (bool = 0; *splitted_str; splitted_str++)
	{
		/*Breaking loop to find the next token*/
		if (splitted_str != string_start)
			if (*splitted_str && *(splitted_str - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (a = 0; delim[a]; a++)
		{
			if (*splitted_str == delim[a])
			{
				*splitted_str = '\0';
				if (splitted_str == string_start)
					string_start++;
				break;
			}
		}
		if (bool == 0 && *splitted_str)  /*Str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (string_start);
}

/**
 * _isdigit - defines if the string or strings passed be a number
 *
 * @s: input string
 * Return: 1 if string is a number. 0 in other case.
 */

int _isdigit(const char *s)
{
	unsigned int c;

	for (c = 0; s[c]; c++)
	{
		if (s[c] < 48 || s[c] > 57)
			return (0);
	}
	return (1);
}
