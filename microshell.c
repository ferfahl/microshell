#include "microshell.h"

int	ft_putstr_2(char *str, char *arg)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	if (arg)
	{
		i = 0;
		while (arg[i])
		{
			write(2, &arg[i], 1);
			i++;
		}
	}
	write(2, "\n", 1);
	return (1);
}

int	cd_micro(char *argv[], int i)
{
	if (i != 2)
		return (ft_putstr_2("error: cd: bad arguments", NULL));
	else if (chdir(argv[1]) != 0)
		return (ft_putstr_2("error: cd: cannot change directory to ", NULL));
	return (0);
}

int	exeggutor(char *argv[], char *envp[], int i, int fd_mod)
{
	argv[i] = NULL;
	dup2(fd_mod, STDIN);
	close(fd_mod);
	execve(argv[0], argv, envp);
	return (ft_putstr_2("error: cannot execute ", argv[0]));
}

int	main(int argc, char *argv[], char *envp[])
{
	int	index;
	int	fd[2];
	int	fd_mod;
	int	status;
	int	pid;

	index = 0;
	status = 0;
	if (argc > 1)
	{
		fd_mod = dup(STDIN);
		while (argv[index] && argv[++index])
		{
			argv = argv + index;
			index = 0;
			while (argv[index] && strcmp(argv[index], "|") && strcmp(argv[index], ";"))
				index++;
			if (!strcmp(argv[0], "cd"))
				status = cd_micro(argv, index);
			else if (index != 0 && (argv[index] == NULL || !strcmp(argv[index], ";")))
			{
				pid = fork();
				if (!pid)
					status = exeggutor(argv, envp, index, fd_mod);
				else
				{
					close (fd_mod);
					while (waitpid(-1, NULL, WUNTRACED) != -1)
						;
					fd_mod = dup(STDIN);
				}
			}
			else if (index != 0 && !strcmp(argv[index], "|"))
			{
				pipe(fd);
				pid = fork();
				if (!pid)
				{
					dup2(fd[1], STDOUT);
					close(fd[0]);
					close(fd[1]);
					status = exeggutor(argv, envp, index, fd_mod);
				}
				else
				{
					close(fd[1]);
					close(fd_mod);
					fd_mod = fd[0];
				}
			}

		}
		close(fd_mod);
	}
	return (status);
}