#include "main.h"

/**
 * _memcpy - To copy information between various void pointers.
 * @newptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 *
 * Return: no return.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *character_pointer = (char *)ptr;
	char *char_newpointer = (char *)newptr;
	unsigned int a;

	for (a = 0; a < size; a++)
		char_newpointer[a] = character_pointer[a];
}

/**
 * _realloc - used to reallocate a memory block.
 * @ptr: pointer to the memory which is previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: returns a ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newpointer;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newpointer = malloc(new_size);
	if (newpointer == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newpointer, ptr, new_size);
	else
		_memcpy(newpointer, ptr, old_size);

	free(ptr);
	return (newpointer);
}

/**
 * _reallocdp - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */


char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newpointer;
	unsigned int a;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newpointer = malloc(sizeof(char *) * new_size);
	if (newpointer == NULL)
		return (NULL);

	for (a = 0; a < old_size; a++)
		newpointer[a] = ptr[a];

	free(ptr);

	return (newpointer);
}
