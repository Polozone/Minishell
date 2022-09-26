
#include "../../includes/minishell.h"

void	check_cmd(t_cmd_lst *tmp);

void	_set_dup_infile(t_cmd_lst *node)
{
	if ((_is_infile(node)))
	{
		node->infile = open(node->file[_last_infile(node) - 1], O_RDWR);
		node->redir_fd[node->index_fd] = node->infile;
		node->index_fd++;
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
		_open_all_outfile(node);
		if (node->redir_type[_last_outfile(node)] == 2)
			node->outfile = open(node->file[_last_outfile(node)], O_CREAT | O_RDWR | O_APPEND, 0644); // DONT FORGET TO PROTECT THIS OPEN
		else if (node->redir_type[_last_outfile(node)] == 1)
			node->outfile = open(node->file[_last_outfile(node)], O_CREAT | O_RDWR, 0644); // DONT FORGET TO PROTECT THIS OPEN
		node->redir_fd[node->index_fd] = node->outfile;
		node->index_fd++;
		if (dup2(node->outfile, 1) == -1)
		{
			write(2, "dup2 failed to run\n", 19);
			// FREE AND EXIT
		}
	}
}

void	close_pipe(t_prg *data)
{
	int		i;

	i = 0;
	// dprintf(2, "nbr == %d\n\n", data->cmd_nbr);
	while (i < ((data->cmd_nbr - 1) * 2))
	{
		// dprintf(2, "Closing pipe...(%d)\n", i);
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
	// dprintf(2, "[%d]cmd(in execve) ==%s   {nbr cmd = %d}\n", tmp->index, tmp->cmd_and_dep[0], data->cmd_nbr);
	if (execve(tmp->path, tmp->cmd_and_dep, data->envp) == -1)
		perror("execve: ");
	// free ALL
	exit (0);
}

void	_redir_first_cmd(t_cmd_lst	*node, t_prg *data)
{
	if (_is_infile(node))
		_set_dup_infile(node);
	if (_is_outfile(node))
		_set_dup_outfile(node, data);
	else
	{
		if (data->cmd_nbr != 1)
			dup2(data->pipe[1], 1);
	}
}

void	_redir_in_pipes(t_cmd_lst	*node, t_prg *data)
{
	if (_is_infile(node))
		_set_dup_infile(node);
	else
		dup2(data->pipe[(node->index - 1) * 2], 0);
	if (_is_outfile(node))
		_set_dup_outfile(node, data);
	else
		dup2(data->pipe[(node->index * 2) + 1], 1);
}

void	_redir_last_cmd(t_cmd_lst *node, t_prg *data)
{
	if (_is_infile(node))
		_set_dup_infile(node);
	else
		dup2(data->pipe[(node->index - 1) * 2], 0);
	if (_is_outfile(node))
		_set_dup_outfile(node, data);
}

void	_set_pipes(t_prg	*data, t_cmd_lst	*node)
{
	if (node->index == 0)
		_redir_first_cmd(node, data);
	else if (node->index != data->cmd_nbr - 1)
		_redir_in_pipes(node, data);
	else if (node->index == data->cmd_nbr - 1 && data->cmd_nbr != 1)
		_redir_last_cmd(node, data);
}

void	_heredoc(t_prg *data, t_cmd_lst *tmp, int i)
{
	char	*line;
	char	*buf;

	line = NULL;
	int longest;
	while (1)
	{
		longest = ft_strlen(tmp->heredoc_delimiter[i]);
		write(1, "> ", 2);
		buf = get_next_line(0);
		if (ft_strlen(buf) > longest)
			longest = ft_strlen(buf) - 1;
		if (ft_strncmp(buf, tmp->heredoc_delimiter[i], longest) == 0)
		{
			free(buf);
			break ;
		}
		line = ft_strjoin_gnl(line, buf, -1, 0);
		free(buf);
	}
	write(tmp->pipe_hd[1], line, ft_strlen(line));
	free(line);
}

void	_set_fd(t_cmd_lst *tmp, t_prg *data)
{
	_init_fd(data);
	_set_pipes(data, tmp);
	if (tmp->heredoc_delimiter[0])
	{
		dup2(tmp->pipe_hd[0], 0);
		close(tmp->pipe_hd[0]);
		close(tmp->pipe_hd[1]);
	}
	close_pipe(data);
	if (is_builtin_fork(data, tmp))
		exit (0) ;
	_ft_execve(data, tmp);
	return ;
}

void	check_cmd(t_cmd_lst *tmp)
{
	dprintf(2, "\n\ncmd == %s\n\n", tmp->cmd_and_dep[0]);
	return ;
}

	// char buffer[50];
	// dprintf(2, "fd[lecture] == %d\n", data->pipe[0]);
	// read(data->pipe[0], buffer, 49);
	// buffer[49] = 0;
	// dprintf(2, "buffer == %s\n", buffer);