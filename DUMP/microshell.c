
int	ft_list_size(char **list)
{
	int	count;

	count = 0;
	while (list[count])
		count++;
	return (count);
}

int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (str[count])
		count++;
	return (count);
}

int	count_till(int argc, char *list[], char *str)
{
	int	count;

	count = 0;
	if (!list)
		return (0);
	printf("list[%d] = %s\n", count, list[count]);
	while (count < argc && list[count])
	{
		if (!strncmp(list[count], str, ft_strlen(str)))
			break ;
		count++;
	}
	printf("count = %d", count);
	return (count);
}

char	**get_temp(int argc, char *argv[], int index)
{
	char	**piped;
	int		count;
	int		size;

	count = 0;
		// printf("\thi\n");
	size = count_till(argc, argv + index, ";\0");
	piped = malloc(sizeof(char *) * (size + 1));
	if (!piped)
		return (NULL);
	while (count < argc && strncmp(argv[index + count], ";\0", 2))
	{
		piped[count] = argv[index + count];
		count++;
	}
	piped[count] = NULL;
	return (piped);
}

t_semicolon	*init_micro(int argc, char *argv[], char *envp[])
{
	t_semicolon	*semi;
	t_semicolon	*head;
	int		count;
	int		size;
	// char	**middle;

	count = 0;
	size = 0;
	semi = malloc(sizeof(t_semicolon));
	(void)envp;
	if (!semi)
		return (NULL);
	head = semi;
	while (count < argc)
	{
		semi->line = get_temp(argc, argv, count);
		printf("\tcount in init_micro = %d\n", count);
		count = ft_list_size(semi->line) + count;
		if (count == argc - 1)
			break ;
		semi->next = malloc(sizeof(t_semicolon));
		semi = semi->next;
	}
	return (head);
}

void	test_micro(t_micro *ms)
{
	printf("ms->envp[0] = %s\n", ms->envp[0]);
	// printf("ms->head_s->line[0] = %s\n", ms->head_s->line[0]);
}

int	first_funct(int argc, char *argv[], char *envp[])
{
	t_micro	*ms;

	ms = malloc(sizeof(t_micro));
	if (!ms)
		return (-1);
	ms->envp = envp;
	ms->head_s = init_micro(argc, argv, envp);
	test_micro(ms);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	status;

	status = 0;
	if (argc > 1)
		status = first_funct(argc, argv, envp);
	exit (status);
}