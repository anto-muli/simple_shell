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
	info_t info[] = { INFO_INIT };
	int fd = 2;

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
				_displaystr(av[0]);
				_displaystr(": 0: Can't open ");
				_displaystr(av[1]);
				_displaychar('\n');
				_displaychar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	generate_env_list(info);
	scan_hist(info);
	myhsh(info, av);
	return (EXIT_SUCCESS);
}
