#include "main.h"

/**
 * aux_help - Help information for the builtin help.
 * Return: no return
 */

void aux_help(void)
{
	char *aux_helper = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
	aux_helper = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
	aux_helper = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
}

/**
 * aux_help_alias - Gives help info for the builtin aliases.
 *
 * Return: no return
 */

void aux_help_alias(void)
{
	char *aux_helper = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
	aux_helper = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
}

/**
 * aux_help_cd - Help information for the builtin alias.
 * Return: no return
 */

void aux_help_cd(void)
{
	char *aux_helper = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
	aux_helper = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
}
