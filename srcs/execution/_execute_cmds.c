
#include "../../includes/minishell.h"

void	close_pipe(t_prg *data)
{
	int		i;

	i = 0;
	while (i < (data->cmd_nbr - 1) * 2)
	{
		// printf("awdawd");
		close(data->pipe[i]);
		i++;
	}
}

int		_execute_cmds(t_prg *data, size_t i)
{
	int j = 0;
	// printf("size == %d\n", ft_strlen_2d(data->cmd_list->file));
	while (data->cmd_list->file[j])
	{
		printf("file == %s\n", data->cmd_list->file[j]);
		printf("test\n");
		j++;
	}
	close_pipe(data);
	exit(0);
	return (0);
}