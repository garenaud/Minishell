

#include "../minishell.h"

char    *path_list(char *env[])
{
	int	i;

	i = 0;
	while (*(env + i) != NULL)
	{
		if (*(*(env + i)) == 'P' && *(*(env + i) + 1) == 'A'
			&& *(*(env + i) + 2) == 'T' && *(*(env + i) + 3) == 'H'
			&& *(*(env + i) + 4) == '=')
			return (env[i]);
		i++;
	}
    return (NULL);
}

void    create_env_list(t_list **env_list, char *env[])
{//leak
	int	i;

	i = 0;
	while (*(env + i) != NULL)
	{
		push(env_list, env[i]);
		i++;
	}
   *env_list = reverse(env_list);
    printll(*env_list);
}