#include "shell.h"

/**
 * hsh - Main function for the shell program.
 *
 * @info: Pointer to a structure containing information about the shell.
 * @av:   Argument vector from the main() function.
 *
 * Return: 0 on success, 1 on error, or an error code.
 */
int hsh(info_t *info, char **av)
{
	ssize_t v = 0;
	int built_in_result = 0;

	while (v != -1 && built_in_result != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(FLUSH_BUFFER);
		v = get_input(info);
		if (v != -1)
		{
			set_info(info, av);
			built_in_result = find_and_execute_builtin(info);
			if (built_in_result == -1)
				find_and_execute_builtin(info);
		}
		else if (interactive(info))
		{
			_putchar('\n');
		}
		free_info(info, 0);
	}
	writeHistoryToFile(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (built_in_result == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (built_in_result);
}


/**
 * find_and_execute_builtin - Find and execute a built-in command.
 *
 * @info: Pointer to a structure containing information about the shell.
 *
 * Return: -1 if the built-in command is not found,
 * 0 if the built-in command is executed successfully,
 * 1 if the built-in command is found but not successful,
 * -2 if the built-in command signals an exit().
 */
int find_and_execute_builtin(info_t *info)
{
	{
		int x, builtin_in_ret = -1;

		typedef struct builtin_table {
			char *type;
			int (*func)(info_t *);
		} builtin_table;

		builtin_table builtintbl[] = {
			{"exit", _myexit},
			{"env", _printEnvironment},
			{"help", _myhelp},
			{"history", _myhistory},
			{"setenv", _mysetenv},
			{"unsetenv", _myunsetenv},
			{"cd", _mycd},
			{"alias", _myalias},
			{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (compare_strings(info->argv[0], builtintbl[x].type) == 0)
		{
			info->line_count++;
			builtin_in_ret = builtintbl[x].func(info);
			break;
		}
	return (builtin_in_ret);
}

/**
 * find_and_execute_command - Find and execute a command in the PATH.
 *
 * @info: Pointer to a structure containing information about the shell.
 *
 * Return: void
 */
void find_and_execute_command(info_t *info)
{
	char *path = NULL;
	int x, l;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (x = 0, l = 0; info->arg[x]; x++)
		if (!is_delim(info->arg[x], " \t\n"))
		l++;
	if (!l)
		return;

	path = findCommandPath(info, _retrieveEnvironmentValue(info, "PATH="),
			info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_and_execute_command(info);
	}
	else
	{
		if ((interactive(info) || _retrieveEnvironmentValue(info, "PATH=")
					|| info->argv[0][0] == '/') && isExecutableCommand(info, info->argv[0]))
			fork_and_execute_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			displayErrorMessage(info, "not found\n");
		}
	}
}

/**
 * fork_and_execute_command - Forks a new process to execute a
 * command using execve.
 *
 * @info: Pointer to a structure containing information about the shell.
 *
 * Return: void
 */
void fork_and_execute_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Fork error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
			{
				exit(126);
			}
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
			{
				displayErrorMessage(info, "Permission denied\n");
			}
		}
	}
}
