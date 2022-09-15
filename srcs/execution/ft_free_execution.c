
#include "../../includes/minishell.h"

void	_free_pipes(t_prg *data)
{
	// free(data->pipe);
}

void	_ft_free_exe(t_prg *data)
{
	_free_pipes(data);
}