#include "main.h"

/**
 * is_cdir - checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 *
 * Return: 1 if path == searchable in the cd, 0 otherwise.
 */

int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - used to locates a command
 *
 * @cmd: store command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *_which(char *cmd, char **_environ)
{
	char *path, *pointer_path, *token_path, *directory;
	int length_dir, length_cmd, a;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		pointer_path = _strdup(path);
		length_cmd = _strlen(cmd);
		token_path = _strtok(pointer_path, ":");
		a = 0;
		while (token_path != NULL)
		{
			if (is_cdir(path, &a))
				if (stat(cmd, &st) == 0)
					return (cmd);
			length_dir = _strlen(token_path);
			directory = malloc(length_dir + length_cmd + 2);
			_strcpy(directory, token_path);
			_strcat(directory, "/");
			_strcat(directory, cmd);
			_strcat(directory, "\0");
			if (stat(directory, &st) == 0)
			{
				free(pointer_path);
				return (directory);
			}
			free(directory);
			token_path = _strtok(NULL, ":");
		}
		free(pointer_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - determines if is an executable
 *
 * @datash: data structure
 * Return: 0 if is not an executable, other number if it does
 */

int is_executable(data_shell *datash)
{
	struct stat st;
	int j;
	char *input_x;

	input_x = datash->args[0];
	for (j = 0; input_x[j]; j++)
	{
		if (input_x[j] == '.')
		{
			if (input_x[j + 1] == '.')
				return (0);
			if (input_x[j + 1] == '/')
				continue;
			else
				break;
		}
		else if (input_x[j] == '/' && j != 0)
		{
			if (input_x[j + 1] == '.')
				continue;
			j++;
			break;
		}
		else
			break;
	}
	if (j == 0)
		return (0);

	if (stat(input_x + j, &st) == 0)
	{
		return (j);
	}
	get_error(datash, 127);
	return (-1);
}

/**
 * check_error_cmd - verifies if user has acess permissions
 *
 * @dir: destination directory
 * @datash: data structure
 * Return: 1 if there is an error, 0 if not
 */

int check_error_cmd(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		get_error(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - executes command lines
 *
 * @datash: data relevant (args and input)
 * Return: 1 on success.
 *
 */
int cmd_exec(data_shell *datash)
{
	pid_t p_d;
	pid_t w_p_d;
	int states;
	int execut;
	char *directory;
	(void) w_p_d;

	execut = is_executable(datash);
	if (execut == -1)
		return (1);
	if (execut == 0)
	{
		directory = _which(datash->args[0], datash->_environ);
		if (check_error_cmd(directory, datash) == 1)
			return (1);
	}

	p_d = fork();
	if (p_d == 0)
	{
		if (execut == 0)
			directory = _which(datash->args[0], datash->_environ);
		else
			directory = datash->args[0];
		execve(directory + execut, datash->args, datash->_environ);
	}
	else if (p_d < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			w_p_d = waitpid(p_d, &states, WUNTRACED);
		} while (!WIFEXITED(states) && !WIFSIGNALED(states));
	}

	datash->status = states / 256;
	return (1);
}
