#include "microshell.h"

void	get_cmd(t_micro **ms, char *cmd)
{
	t_micro	*tmp;
	t_micro	*new;

	tmp = *ms;
	new = malloc(sizeof(t_micro));
	if (!new)
		return ;
	new->cmd = cmd;
	new->next = NULL;
	if (!tmp)
	{
		*ms = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_micro	*init_micro(int argc, char *argv[], char *envp[])
{
	t_micro	*ms;
	int		count;

	count = 0;
	ms = malloc(sizeof(t_micro));
	if (!ms)
		return (NULL);
	while (count < argc)
	{
		if (strncmp(argv[count], ";\0", 2))

		get_cmd(&ms, argv[count]);
		count++;
	}
	ms->envp = envp;
	return (ms);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_micro	*ms;

	ms = init_micro(envp);

}