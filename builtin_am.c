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

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitStatus = _erratoi(info->argv[1]);
		if (exitStatus == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
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
	int s = 0;

	x = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		newDir = _retrieveEnvironmentValue(info, "HOME = ");
		if (!newDir)
			chdirResult = /* TODO: what should this be? */
				chdir((newDir = _retrieveEnvironmentValue(info, "PWD=")) ?
						newDir : "/");
		else
			chdirResult = chdir(newDir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_retrieveEnvironmentValue(info, "OLDPWD="))
		{
			_puts(x);
			_putchar('\n');
			return (1);
		}
		_puts(_retrieveEnvironmentValue(info, "OLDPWD="));
		_putchar('\n');
		chdirResult = chdir((newDir = _retrieveEnvironmentValue(info, "OLDPWD=")) ? newDir : "/");
	}
	else
		chdirResult = chdir(info->argv[1]);
	if (chdirResult == -1)
	{
		print_error(info, "do not cd into ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD"), _retrieveEnvironmentValue(info, "PWD=");
		_setenv(info, "PWD"), getcwd(info, x);
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
	char **arguments;

	arguments = info->argv;
	_puts("calls 'help' command, but the function isn't implemented.\n");
	if (0)
		_puts(arguments); /*temp att_unused workaround */
			return (0);
}

