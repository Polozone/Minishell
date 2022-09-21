
#include "../../includes/minishell.h"

void	_ft_free_exe(t_prg *data)
{
	ft_free_1d((void**)&data->pid);
	ft_free_1d((void**)&data->pipe);
	ft_free_1d((void**)&data->cmd_list->redir_fd);
}