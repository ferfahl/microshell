#include "microshell.h"

#include <stdio.h>

void	test_micro(t_micro *ms)
{
	printf("ms->envp[0] = %s\n", ms->envp[0]);
	printf("ms->head_s->line[0] = %s\n", ms->head_s->line[0]);
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