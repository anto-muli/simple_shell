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
	int exitcheck;

	if (info->argv[1])  /* If an exit argument is provided */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
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
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _fetchenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what this should be? */
				chdir((dir = _fetchenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcompare(info->argv[1], "-") == 0)
	{
		if (!_fetchenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_fetchenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what this should be? */
			chdir((dir = _fetchenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _fetchenv(info, "PWD="));
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
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temporary workaround for unused attributes */
	return (0);
}
