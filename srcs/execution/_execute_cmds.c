
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

// < infile cat | wc -l > outfile666 | cat infile2 > outfile3

// cat infile | wc -l >> outfile66

// < infile cat | wc -l >> outfile666

// < infile cat > outfile666

// < infile cat > outfile666 | ls > outfile2 > outfile3 > outfile4

void	_init_fd(t_prg *data)
{
	t_cmd_lst	*tmp;
	
	tmp = data->cmd_list;
	while (tmp)
	{
		tmp->infile = 0;
		tmp->outfile = 1;
		tmp = tmp->next;
	}
}

void	_ft_execve(t_prg *data, t_cmd_lst *tmp)
{
	if (execve(tmp->path, tmp->cmd_and_dep, data->envp) == -1)
		write(2, "Execve Failed to run\n", 21);
}

void	_set_dup_infile(t_cmd_lst *node)
{
	if (_is_infile(node))
	{
		node->infile = open(node->file[_last_infile(node) - 1], O_RDWR);
		if (dup2(node->infile, 0) == -1)
		{
			write(2, "dup2 failed to run\n", 19);
			// FREE AND EXIT
		}
	}
}

void	_set_dup_outfile(t_cmd_lst *node)
{
	if (_is_outfile(node))
	{
		node->outfile = open(node->file[_last_outfile(node)], O_CREAT | O_RDWR, 0644);
		if (dup2(node->outfile, 1) == -1)
		{
			write(2, "dup2 failed to run\n", 19);
			// FREE AND EXIT
		}
	}
}

void	_setup_dup_pipe(t_cmd_lst *node, t_prg *data)
{
	if (!_is_infile(node) && node->index == 0)
	{
		dprintf(2, "NO INFILE AND FIRST NODE (%s)\n", node->cmd_and_dep[0]);
		dup2(data->pipe[1], 0);
	}
	else if (!_is_outfile(node) && (node->index + 1) == data->cmd_nbr)
	{
		dprintf(2, "NO OUTFILE AND LAST NODE (%s)\n", node->cmd_and_dep[0]);
		dup2(1, data->pipe[(node->index - 1) * 2]);
	}
	else 
	{
		dup2(data->pipe[(node->index * 2)], 0);
		dup2(data->pipe[node->index + 1], 1);
	 	dprintf(2, "inside NODE(%s)\n", node->cmd_and_dep[0]);
	}
}

// 				L   E
// i =	0   	0   1
// i = 1	    2   3
// i = 2	    4   5
// i = 3	    6   7
// i = 4		8   9
// i = 5		10  11   
// i = 6		12	13

void	_set_fd(t_cmd_lst *tmp, t_prg *data)
{
	_init_fd(data);
	_setup_dup_pipe(tmp, data);
	_set_dup_infile(tmp);
	_set_dup_outfile(tmp);
	close_pipe(data);
	_ft_execve(data, tmp);
	return ;
}

int		_execute_cmds(t_prg *data, size_t i, t_cmd_lst *tmp)
{
	_set_fd(tmp, data);
	return (0);
}