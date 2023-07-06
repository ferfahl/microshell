#include "microshell.h"

int	ft_list_size(char **list)
{
	int	count;

	count = 0;
	while (list[count])
		count++;
	return (count);
}

int	count_till(char *list[], char *str)
{
	int	count;

	count = 0;
	while (strncmp(list[count], str, 2))
		count++;
	return (count);
}
