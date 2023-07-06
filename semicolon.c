#include "microshell.h"

char	**get_temp(char *argv[], int index)
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

t_semicolon	*init_micro(int argc, char *argv[], char *envp[])
{
	t_semicolon	*semi;
	t_semicolon	*head;
	int		count;
	int		size;
	// char	**middle;

	count = 1;
	size = 0;
	semi = malloc(sizeof(t_semicolon));
	(void)envp;
	if (!semi)
		return (NULL);
	head = semi;
	while (count < argc)
	{
		semi->line = get_temp(argv, count);
		count = ft_list_size(semi->line) + count;
		if (count == argc)
			break ;
		semi->next = malloc(sizeof(t_semicolon));
		semi = semi->next;
	}
	return (head);
}
