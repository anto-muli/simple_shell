#include "shell.h"

/**
 * myhsh - Main function for the shell program.
 *
 * @info: Pointer to a structure containing information about the shell.
 * @av:   Argument vector from the main() function.
 *
 * Return: 0 on success, 1 on error, or an error code.
 */
int myhsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		wipe_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = fetch_input(info);
		if (r != -1)
		{
			place_info(info, av);
			builtin_ret = detect_builtin(info);
			if (builtin_ret == -1)
				detect_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		release_info(info, 0);
	}
	record_hist(info);
	release_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * detect_builtin - Find and execute a built-in command.
 *
 * @info: Pointer to a structure containing information about the shell.
 *
 * Return: -1 if the built-in command is not found,
 * 0 if the built-in command is executed successfully,
 * 1 if the built-in command is found but not successful,
 * -2 if the built-in command signals an exit().
 */
int detect_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _findenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};
	for (i = 0; builtintbl[i].type; i++)
		if (_strcompare(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * detect_cmd - Find and execute a command in the PATH.
 *
 * @info: Pointer to a structure containing information about the shell.
 *
 * Return: void
 */
void detect_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = detect_path(info, _fetchenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		split_cmd(info);
	}
	else
	{
		if ((interactive(info) || _fetchenv(info, "PATH=")
					|| info->argv[0][0] == '/') && confirm_cmd(info, info->argv[0]))
			split_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * split_cmd - Forks a new process to execute a
 * command using execve.
 *
 * @info: Pointer to a structure containing information about the shell.
 *
 * Return: void
 */
void split_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, fetch_environ(info)) == -1)
		{
			release_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
