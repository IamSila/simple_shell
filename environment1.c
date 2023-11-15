#include "main.h"

/**
 * cmp_env_name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */

int cmp_env_name(const char *nenv, const char *name)
{
	int a;

	for (a = 0; nenv[a] != '='; a++)
	{
		if (nenv[a] != name[a])
		{
			return (0);
		}
	}

	return (a + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: if foind return value of the environment.
 * , returns NULL if value not found.
 */

char *_getenv(const char *name, char **_environ)
{
	char *pointer_env;
	int j, mov;

	/* Initialize ptr_env value */
	pointer_env = NULL;
	mov = 0;

	/* Compare all environment variables */
	/* environ is declared in the header file */

	for (j = 0; _environ[j]; j++)
	{
		/* If name and env are equal */
		mov = cmp_env_name(_environ[j], name);
		if (mov)
		{
			pointer_env = _environ[j];
			break;
		}
	}

	return (pointer_env + mov);
}

/**
 * _env - prints the evironment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int _env(data_shell *datash)
{
	int a, b;

	for (a = 0; datash->_environ[a]; a++)
	{

		for (b = 0; datash->_environ[a][b]; b++)
			;

		write(STDOUT_FILENO, datash->_environ[a], b);
		write(STDOUT_FILENO, "\n", 1);
	}

	datash->status = 0;

	return (1);
}
