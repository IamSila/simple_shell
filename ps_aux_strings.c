#include "main.h"

/**
 * _strcat - concatenate two strings
 * @dest: char pointer the destination of the copied str
 * @src: const char pointer the source of str
 *
 * Return: the dest
 */

char *_strcat(char *dest, const char *src)
{
	int a;
	int b;

	for (a = 0; dest[a] != '\0'; a++)
		;

	for (b = 0; src[b] != '\0'; b++)
	{
		dest[a] = src[b];
		a++;
	}

	dest[a] = '\0';
	return (dest);
}

/**
 * *_strcpy - Copies the string pointed to by src.
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 *
 * Return: the dest.
 */


char *_strcpy(char *dest, char *src)
{

	size_t i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return (dest);
}


/**
 * _strcmp - Function that compares two strings.
 * @s1: type string to be  compared
 * @s2: type the string to be compared
 *
 * Return: Always 0.
 */


int _strcmp(char *s1, char *s2)
{
	int j;

	for (j = 0; s1[j] == s2[j] && s1[j]; j++)
		;

	if (s1[j] > s2[j])
		return (1);
	if (s1[j] < s2[j])
		return (-1);
	return (0);
}

/**
 * _strchr - locates a character in a string,
 * @s: a string.
 * @c: a character.
 *
 * Return: the pointer to the first occurrence of the character c.
 */

char *_strchr(char *s, char c)
{
	unsigned int k = 0;

	for (; *(s + k) != '\0'; k++)
		if (*(s + k) == c)
			return (s + k);
	if (*(s + k) == c)
		return (s + k);
	return ('\0');
}

/**
 * _strspn - used to get the length of a prefix substring.
 * @s: the initial segment.
 * @accept: accepted byte(s).
 *
 * Return: the number of accepted bytes.
 */

int _strspn(char *s, char *accept)
{
	int a, b, bool;

	for (a = 0; *(s + a) != '\0'; a++)
	{
		bool = 1;
		for (b = 0; *(accept + b) != '\0'; b++)
		{
			if (*(s + a) == *(accept + b))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (a);
}
