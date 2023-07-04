#include "microshell.h"

int	count_till(char *list[], char *str)
{
	int	count;

	count = 0;
	while (strncmp(list[count], str, 2))
		count++;
	return (count);
}

char	**get_temp(t_semicolon *semi, char *argv[], int index)
{
	char	**piped;
	int		count;
	int		size;

	count = 0;
	size = count_till(argv + index, ";\0");
	piped = malloc(sizeof(char *) * (size + 1));
	if (!piped)
		return (NULL);
	while (strncmp(argv[index + count], ";\0", 2))
	{
		piped[count] = argv[index + count];
		count++;
	}
	piped[count] = NULL;
	return (piped);
}
int	ft_list_size(char **list)
{
	int	count;

	count = 0;
	while (list[count])
		count++;
	return (count);
}

t_semicolon	*init_micro(int argc, char *argv[], char *envp[])
{
	t_semicolon	*semi;
	t_semicolon	*head;
	int		count;
	int		size;
	char	**middle;

	count = 1;
	size = 0;
	semi = malloc(sizeof(t_semicolon));
	if (!semi)
		return (NULL);
	head = semi;
	while (count < argc)
	{
		semi->line = get_temp(semi, argv, count);
		count = ft_list_size(semi->line) + count;
		if (count == argc)
			break ;
		semi->next = malloc(sizeof(t_semicolon));
		semi = semi->next;
	}
	return (head);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_micro	*ms;

	ms = malloc(sizeof(t_micro));
	if (!ms)
		return (NULL);
	ms->envp = envp;
	ms->head_s = init_micro(argc, argv, envp);

}