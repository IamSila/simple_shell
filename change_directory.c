#include "main.h"

/**
 * cd_dot - changes to the parent directory
 *
 * @datash: data relevant (environ)
 *
 * Return: no return
 */

void cd_dot(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *directory, *copy_pwd, *cp_strt_pwd;

	getcwd(pwd, sizeof(pwd));
	copy_pwd = _strdup(pwd);
	set_env("OLDPWD", copy_pwd, datash);
	directory = datash->args[1];
	if (_strcmp(".", directory) == 0)
	{
		set_env("PWD", copy_pwd, datash);
		free(copy_pwd);
		return;
	}
	if (_strcmp("/", copy_pwd) == 0)
	{
		free(copy_pwd);
		return;
	}
	cp_strt_pwd = copy_pwd;
	rev_string(cp_strt_pwd);
	cp_strt_pwd = _strtok(cp_strt_pwd, "/");
	if (cp_strt_pwd != NULL)
	{
		cp_strt_pwd = _strtok(NULL, "\0");

		if (cp_strt_pwd != NULL)
			rev_string(cp_strt_pwd);
	}
	if (cp_strt_pwd != NULL)
	{
		chdir(cp_strt_pwd);
		set_env("PWD", cp_strt_pwd, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(copy_pwd);
}

/**
 * cd_to - changes to directory which is given
 * by the user
 *
 * @datash: data relevant (directories)
 * Return: no return
 */


void cd_to(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *directory, *copy_pwd, *copy_dir;

	getcwd(pwd, sizeof(pwd));

	directory = datash->args[1];
	if (chdir(directory) == -1)
	{
		get_error(datash, 2);
		return;
	}

	copy_pwd = _strdup(pwd);
	set_env("OLDPWD", copy_pwd, datash);

	copy_dir = _strdup(directory);
	set_env("PWD", copy_dir, datash);

	free(copy_pwd);
	free(copy_dir);

	datash->status = 0;

	chdir(directory);
}

/**
 * cd_previous - changes to the previous directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */

void cd_previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *print_pwd, *print_oldpwd, *copy_pwd, *copy_oldpwd;

	getcwd(pwd, sizeof(pwd));
	copy_pwd = _strdup(pwd);

	print_oldpwd = _getenv("OLDPWD", datash->_environ);

	if (print_oldpwd == NULL)
		copy_oldpwd = copy_pwd;
	else
		copy_oldpwd = _strdup(print_oldpwd);

	set_env("OLDPWD", copy_pwd, datash);

	if (chdir(copy_oldpwd) == -1)
		set_env("PWD", copy_pwd, datash);
	else
		set_env("PWD", copy_oldpwd, datash);

	print_pwd = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, print_pwd, _strlen(print_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(copy_pwd);
	if (print_oldpwd)
		free(copy_oldpwd);

	datash->status = 0;

	chdir(print_pwd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */

void cd_to_home(data_shell *datash)
{
	char *print_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	print_pwd = _strdup(pwd);

	home = _getenv("HOME", datash->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", print_pwd, datash);
		free(print_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datash, 2);
		free(print_pwd);
		return;
	}

	set_env("OLDPWD", print_pwd, datash);
	set_env("PWD", home, datash);
	free(print_pwd);
	datash->status = 0;
}
