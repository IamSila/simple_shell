#include "main.h"

/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */

char *copy_info(char *name, char *value)
{
	char *new_one;
	int length_of_name, length_of_value, length;

	length_of_name = _strlen(name);
	length_of_value = _strlen(value);
	length = length_of_name + length_of_value + 2;
	new_one = malloc(sizeof(char) * (length));
	_strcpy(new_one, name);
	_strcat(new_one, "=");
	_strcat(new_one, value);
	_strcat(new_one, "\0");

	return (new_one);
}

/**
 * set_env - sets the environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 *
 * Return: no return
 */

void set_env(char *name, char *value, data_shell *datash)
{
	int j;
	char *variable_env, *name_env;

	for (j = 0; datash->_environ[j]; j++)
	{
		variable_env = _strdup(datash->_environ[j]);
		name_env = _strtok(variable_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[j]);
			datash->_environ[j] = copy_info(name_env, value);
			free(variable_env);
			return;
		}
		free(variable_env);
	}

	datash->_environ = _reallocdp(datash->_environ, j, sizeof(char *) * (j + 2));
	datash->_environ[j] = copy_info(name, value);
	datash->_environ[j + 1] = NULL;
}

/**
 * _setenv - compares environment variable names
 * with the name which has been passed.
 * @datash: data relevant (environment name and environment value)
 *
 * Return: 1 on success.
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - deletes an environment variable
 *
 * @datash: data relevant (environment name)
 *
 * Return: 1 on success.
 */

int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *variable_env, *name_environment;
	int a, b, c;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	c = -1;
	for (a = 0; datash->_environ[a]; a++)
	{
		variable_env = _strdup(datash->_environ[a]);
		name_environment = _strtok(variable_env, "=");
		if (_strcmp(name_environment, datash->args[1]) == 0)
		{
			c = a;
		}
		free(variable_env);
	}
	if (c == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (a));
	for (a = b = 0; datash->_environ[a]; a++)
	{
		if (a != c)
		{
			realloc_environ[b] = datash->_environ[a];
			b++;
		}
	}
	realloc_environ[b] = NULL;
	free(datash->_environ[c]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
