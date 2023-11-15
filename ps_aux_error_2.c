#include "main.h"

/**
 * error_env - error message for env in get_env.
 * @datash: data relevant (counter, arguments)
 * Return: error message.
 */

char *error_env(data_shell *datash)
{
	int len;
	char *error;
	char *ver_string;
	char *message;

	ver_string = aux_itoa(datash->counter);
	message = ": Unable to add or remove from environment\n";
	len = _strlen(datash->av[0]) + _strlen(ver_string);
	len += _strlen(datash->args[0]) + _strlen(message) + 4;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(error);
		free(ver_string);
		return (NULL);
	}

	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_string);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, message);
	_strcat(error, "\0");
	free(ver_string);

	return (error);
}


/**
 * error_path_126 - error message for path and failure denied permission.
 * @datash: data relevant (counter, arguments).
 *
 * Return: The error string.
 */


char *error_path_126(data_shell *datash)
{
	int len;
	char *ver_string;
	char *error;

	ver_string = aux_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(ver_string);
	len += _strlen(datash->args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(error);
		free(ver_string);
		return (NULL);
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_string);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_string);
	return (error);
}
