#include "shell.h"

/**
  * _myexit - Function to exit the shell
  * @info: Pointer to a structure containing potential arguments. Used to
  * maintain a consistent function prototype.
  * Return: Exits the shell with a given exit status
  * (0) if info->argv[0] != "exit"
  */
int _myexit(info_t *info)
{
	int exitStatus;

	if (info->argv[1]) /* If an exit argument is provided */
	{
		exitStatus = strToIntWithErrHandling(info->argv[1]);
		if (exitStatus == -1)
		{
			info->status = 2;
			displayErrorMessage(info, "oops illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = strToIntWithErrHandling(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
  * _mycd - Change the current directory of the process
  * @info: Pointer to a structure containing potential arguments. Used to
  * maintain a consistent function prototype.
  * Return: Always returns 0
  */
int _mycd(info_t *info)
{
	char *x, *newDir, buffer[1024];
	int chdirResult;

	x = getcwd(buffer, 1024);
	if (!x)
		_puts("TODO: Include error message for 'getcwd' failure here.");
	if (!info->argv[1])
	{
		newDir = _retrieveEnvironmentValue(info, "HOME=");
		if (!newDir)
			chdirResult = /* TODO: Define the intended purpose of this. */
				chdir((newDir = _retrieveEnvironmentValue(info, "PWD=")) ?
						newDir : "/");
		else
			chdirResult = chdir(newDir);
	}
	else if (compare_strings(info->argv[1], "-") == 0)
	{
		if (!_retrieveEnvironmentValue(info, "OLDPWD="))
		{
			_puts(x);
			_putchar('\n');
			return (1);
		}
		_puts(_retrieveEnvironmentValue(info, "OLDPWD=")), _putchar('\n');
		chdirResult = /* TODO: Define the intended purpose of this */
		chdir((newDir = _retrieveEnvironmentValue(info, "OLDPWD=")) ? newDir : "/");
	}
	else
		chdirResult = chdir(info->argv[1]);
	if (chdirResult == -1)
	{
		displayErrorMessage(info, "oops can't cd into ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _retrieveEnvironmentValue(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
  * _myhelp - Display help information (not yet implemented)
  * @info: Pointer to a structure containing potential arguments
  * used to  a consistent function prototype.
  * Return: Always returns 0
  */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("calls 'help' command, but the function isn't implemented.\n");
	if (0)
		_puts(arg_array); /* Temporary workaround for unused attribute */
			return (0);
}
