
#include "../../includes/minishell.h"

void	close_pipe(t_prg *data)
{
	int		i;

	i = 0;
	while (i < (data->cmd_nbr - 1) * 2)
	{
		close(data->pipe[i]);
		i++;
	}
}

int		_execute_cmds(t_prg *data, size_t i)
{
	printf("i == %zu\n", i);
	int j = 0;
	printf("%s", data->cmd_list->cmd_and_dep[0]);
	// while (data->cmd_list->file[j])
	// {
	// 	printf("file == %s\n", data->cmd_list->file[j]);
	// 	j++;
	// }
	// close_pipe(data);
	return(0);
}