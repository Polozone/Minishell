
#include "../../includes/minishell.h"

void	_set_dup_infile(t_cmd_lst *node)
{
	if ((_is_infile(node)))
	{
		node->infile = open(node->file[_last_infile(node) - 1], O_RDWR);
		if (dup2(node->infile, 0) == -1)
		{
			write(2, "dup2 failed to run\n", 19);
			// FREE AND EXIT
		}
	}
}

void	_set_dup_outfile(t_cmd_lst *node, t_prg *data)
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

// 			L   E
// i =	0   			cmd1
// 			0	1	pipe1
// i = 1	       		cmd2
// 			2	3	pipe2
// i = 2	       		cmd3
// 			4	5	pipe3
// i = 3	    	   	cmd4
// 			6	7	pipe4
// i = 4			   	cmd5
// 			8	9	pipe5
// i = 5		 		cmd6
// 			10	11	pipe6
// i = 6				cmd7

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

void	_set_pipes(t_prg	*data, t_cmd_lst	*node)
{
	if (node->index == 0)
		dup2(data->pipe[1], 1);
	else if (node->index != data->cmd_nbr - 1)
	{
		dup2(data->pipe[(node->index - 1) * 2], 0);
		dup2(data->pipe[(node->index * 2) + 1], 1);
	}
	else if (node->index == data->cmd_nbr - 1)
		dup2(data->pipe[(node->index - 1) * 2], 0);
}

// 			L   E
// i =	0   			cmd1
// 			0	1	pipe1
// i = 1	       		cmd2
// 			2	3	pipe2
// i = 2	       		cmd3
// 			4	5	pipe3
// i = 3	    	   	cmd4
// 			6	7	pipe4
// i = 4			   	cmd5
// 			8	9	pipe5
// i = 5		 		cmd6
// 			10	11	pipe6
// i = 6				cmd7

void	_set_fd(t_cmd_lst *tmp, t_prg *data)
{
	dprintf(2, "cmd number == %d\n", tmp->index);
	_init_fd(data);
	// _setup_dup_pipe(tmp, data);
	// _set_dup_infile(tmp);
	// _set_dup_outfile(tmp);
	_set_pipes(data, tmp);
	close_pipe(data);
	_ft_execve(data, tmp);
	return ;
}

int		_execute_cmds(t_prg *data, size_t i, t_cmd_lst *tmp)
{
	_set_fd(tmp, data);
	return (0);
}