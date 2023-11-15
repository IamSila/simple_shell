#include "main.h"

/**
 * cd_shell - changes current directory
 *
 * @datash: data relevant
 * Return: 1 on success
 */

int cd_shell(data_shell *datash)
{
	char *directory;
	int is_home, is_home2, is_ddash;

	directory = datash->args[1];

	if (directory != NULL)
	{
		is_home = _strcmp("$HOME", directory);
		is_home2 = _strcmp("~", directory);
		is_ddash = _strcmp("--", directory);
	}

	if (directory == NULL || !is_home || !is_home2 || !is_ddash)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", directory) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", directory) == 0 || _strcmp("..", directory) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}
