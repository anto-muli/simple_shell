#include "shell.h"

/**
  * main - the entry point to the code
  * @ac: arguement counter
  * @av: arguement vector
  *
  * Return: zero when it succeeds and  1 if there is an  error
  */
int main(int ac, char **av)
{
	int fd = 2;

	info_t info [1];
	info[0].fname = 0;
	info[0].linecount_flag = 0;
	info[0].env_changed = 0;
	info[0].status = 0;


	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open that buddy ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(FLUSH_BUFFER);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	_populateEnvironmentList(info);
	loadHistoryFromFile(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
