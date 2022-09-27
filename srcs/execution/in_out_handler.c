
#include "../../includes/minishell.h"

int		_last_infile(t_cmd_lst *tmp)
{
	int		i;

	i = 0;
	while (i < tmp->redir_nbr && tmp->redir_type[i] == 0)
		i++;
	return (i);
}

int		_last_outfile(t_cmd_lst *tmp)
{
	int		i;
	int		buffer;

	i = 0;
	buffer = 0;
	while (i < tmp->redir_nbr)
	{
		if (tmp->redir_type[i] == 1 || tmp->redir_type[i] == 2)
			buffer = i;
		i++;
	}
	return (buffer);
}

int		_is_infile(t_cmd_lst *tmp)
{
	int		i;

	i = 0;
	while (i < tmp->redir_nbr)
	{
		if (tmp->redir_type[i] == 0)
			return (1);
		i++;
	}
	return (0);
}

int		_is_outfile(t_cmd_lst *tmp)
{
	int		i;

	i = 0;
	while (i < tmp->redir_nbr)
	{
		if (tmp->redir_type[i] == 1 || tmp->redir_type[i] == 2)
			return (1);
		i++;
	}
	return (0);
}

void _open_all_outfile(t_cmd_lst *node)
{
	int i = 0;
	dprintf(2, "node->redir nbr == %d\n", node->redir_nbr);
	while (i < node->redir_nbr - 1)
	{
		// dprintf(2, "node->file[%d] = %s\n", i, node->file[i]);
		if (node->redir_type[i] == 1 || node->redir_type[i] == 2)
		{
			open(node->file[i], O_CREAT | O_RDWR, 0644);
			// dprintf(2, "%d\n", node->redir_type[i]);
			node->redir_fd[node->index_fd] = open(node->file[i], O_CREAT | O_RDWR, 0644);
			node->index_fd++;
		}
		i++;
	}
}