#include "main.h"

/**
 * aux_help_env - Help information for the builtin env
 *
 * Return: no return
 */

void aux_help_env(void)
{
	char *aux_helper = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
	aux_helper = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));

}

/**
 * aux_help_setenv - provides the help information for the builtin setenv cmd
 * Return: no return
 */

void aux_help_setenv(void)
{

	char *aux_helper = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
	aux_helper = "int replace)\n\t";
	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
	aux_helper = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
}

/**
 * aux_help_unsetenv - Help information for the builtin unsetenv
 * Return: no return
 */

void aux_help_unsetenv(void)
{
	char *aux_helper = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
	aux_helper = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
}


/**
 * aux_help_general - Entry point for help information for the help builtin
 * Return: no return
 */

void aux_help_general(void)
{
	char *aux_helper = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
	aux_helper = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
	aux_helper = "Type 'help name' and find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
	aux_helper = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
	aux_helper = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
	aux_helper = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
	aux_helper = "unsetenv [variable]\n";
	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
}

/**
 * aux_help_exit - Help information fot the builint exit
 * Return: no return
 */

void aux_help_exit(void)
{
	char *aux_helper = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
	aux_helper = "Exit the shell with a status of N. If N is ommited, then it exit";
	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
	aux_helper = "The status is that of the last command executed\n";
	write(STDOUT_FILENO, aux_helper, _strlen(aux_helper));
}
