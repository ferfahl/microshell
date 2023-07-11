#include "microshell.h"

int	close_fds()
{
	int	fd;

	fd = 100;
	while (fd > STDERR)
		close(fd--);
	return (1);
}

int	ft_putstr_2(char *str, char *arg, int check)
{
	int	i;

	i = 0;
	if (check)
		close_fds();
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
		return (ft_putstr_2("error: cd: bad arguments", NULL, 0));
	else if (chdir(argv[1]) != 0)
		return (ft_putstr_2("error: cd: cannot change directory to ", NULL, 0));
	return (0);
}

int	exeggutor(char *argv[], char *envp[], int i, int fd_mod)
{
	argv[i] = NULL;
	dup2(fd_mod, STDIN);
	if (close(fd_mod) == -1)
		exit(ft_putstr_2("error: fatal", NULL, 1));
	close_fds();
	execve(argv[0], argv, envp);
	return (ft_putstr_2("error: cannot execute ", argv[0], 0));
}

int	semicolon(char *argv[], char *envp[], int index, int fd_mod)
{
	int	pid;
	int	status;

	pid = fork();
	if (!pid)
		status = exeggutor(argv, envp, index, fd_mod);
	else
	{
		if (close(fd_mod) == -1)
			exit(ft_putstr_2("error: fatal", NULL, 1));
		while (waitpid(-1, NULL, WUNTRACED) != -1)
			;
		fd_mod = dup(STDIN);
		status = 0;
	}
	return (fd_mod);
}

int	piped(char *argv[], char *envp[], int index, int fd_mod)
{
	int	pid;
	int	fd[2];
	
	if (pipe(fd) == -1)
		exit(ft_putstr_2("error: fatal", NULL, 1));
	pid = fork();
	if (!pid)
	{
		if (dup2(fd[1], STDOUT) == -1)
			exit(ft_putstr_2("error: fatal", NULL, 1));
		if (close(fd[0]) == -1)
			exit(ft_putstr_2("error: fatal", NULL, 1));
		if (close(fd[1]) == -1)
			exit(ft_putstr_2("error: fatal", NULL, 1));
		exeggutor(argv, envp, index, fd_mod);
	}
	else
	{
		if (close(fd[1]) == -1)
			exit(ft_putstr_2("error: fatal", NULL, 1));
		if (close(fd_mod) == -1)
			exit(ft_putstr_2("error: fatal", NULL, 1));
		fd_mod = fd[0];
	}
	return (fd_mod);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	index;
	int	fd_mod;
	int	status;

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
				fd_mod = semicolon(argv, envp, index, fd_mod);
			else if (index != 0 && !strcmp(argv[index], "|"))
				fd_mod = piped(argv, envp, index, fd_mod);
		}
		if	(close(fd_mod) == -1)
			exit(ft_putstr_2("error: fatal", NULL, 1));
	}
	// close_fds();
	return (status);
}


// #include "microshell.h"

// int	ft_putstr_2(char *str, char *arg)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		write(2, &str[i], 1);
// 		i++;
// 	}
// 	if (arg)
// 	{
// 		i = 0;
// 		while (arg[i])
// 		{
// 			write(2, &arg[i], 1);
// 			i++;
// 		}
// 	}
// 	write(2, "\n", 1);
// 	return (1);
// }

// int	cd_micro(char *argv[], int i)
// {
// 	if (i != 2)
// 		return (ft_putstr_2("error: cd: bad arguments", NULL));
// 	else if (chdir(argv[1]) != 0)
// 		return (ft_putstr_2("error: cd: cannot change directory to ", NULL));
// 	return (0);
// }

// int	exeggutor(char *argv[], char *envp[], int i, int fd_mod)
// {
// 	argv[i] = NULL;
// 	dup2(fd_mod, STDIN);
// 	if	(close(fd_mod) == -1)
// 		return (ft_putstr_2("error: fatal", NULL));
// 	execve(argv[0], argv, envp);
// 	return (ft_putstr_2("error: cannot execute ", argv[0]));
// }

// int	main(int argc, char *argv[], char *envp[])
// {
// 	int	index;
// 	int	fd[2];
// 	int	fd_mod;
// 	int	status;
// 	int	pid;

// 	index = 0;
// 	status = 0;
// 	if (argc > 1)
// 	{
// 		fd_mod = dup(STDIN);
// 		while (argv[index] && argv[++index])
// 		{
// 			argv = argv + index;
// 			index = 0;
// 			while (argv[index] && strcmp(argv[index], "|") && strcmp(argv[index], ";"))
// 				index++;
// 			if (!strcmp(argv[0], "cd"))
// 				status = cd_micro(argv, index);
// 			else if (index != 0 && (argv[index] == NULL || !strcmp(argv[index], ";")))
// 			{
// 				pid = fork();
// 				if (!pid)
// 					status = exeggutor(argv, envp, index, fd_mod);
// 				else
// 				{
// 					if	(close(fd_mod) == -1)
// 						return (ft_putstr_2("error: fatal", NULL));
// 					while (waitpid(pid, NULL, WUNTRACED) != -1)
// 						;
// 					fd_mod = dup(STDIN);
// 				}
// 			}
// 			else if (index != 0 && !strcmp(argv[index], "|"))
// 			{
// 				if (pipe(fd) == -1)
// 						return (ft_putstr_2("error: fatal", NULL));
// 				pid = fork();
// 				if (!pid)
// 				{
// 					if (dup2(fd[1], STDOUT) == -1)
// 						return (ft_putstr_2("error: fatal", NULL));
// 					if (close(fd[0]) == -1)
// 						return (ft_putstr_2("error: fatal", NULL));
// 					if (close(fd[1]) == -1)
// 						return (ft_putstr_2("error: fatal", NULL));
// 					status = exeggutor(argv, envp, index, fd_mod);
// 				}
// 				else
// 				{
// 					if (close(fd[1]) == -1)
// 						return (ft_putstr_2("error: fatal", NULL));
// 					if (close(fd_mod) == -1)
// 						return (ft_putstr_2("error: fatal", NULL));
// 					fd_mod = fd[0];
// 				}
// 			}

// 		}
// 		if	(close(fd_mod) == -1)
// 			return (ft_putstr_2("error: fatal", NULL));
// 	}
// 	return (status);
// }
