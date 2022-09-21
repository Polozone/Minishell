
#include "../../includes/minishell.h"

void	ft_free_1d(void	**to_free)
{
	if (*to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
}

void	ft_free_2d(void	***to_free)
{
	if (**to_free)
	{
		free(**to_free);
		**to_free = NULL;
	}
}