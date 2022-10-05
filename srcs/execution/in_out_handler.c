/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:53:40 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/05 18:17:43 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_last_infile(t_cmd_lst *tmp)
{
	int		i;
	int		fd;

	i = 0;
	while (i < tmp->redir_nbr && tmp->redir_type[i] == 0)
	{
		fd = open(tmp->file[i], O_RDONLY);
		_handler_errors_infiles(tmp, i);
		if (fd > 0)
			close(fd);
		i++;
	}
	return (i);
}

int	_last_outfile(t_cmd_lst *tmp)
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

int	_is_infile(t_cmd_lst *tmp)
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

int	_is_outfile(t_cmd_lst *tmp)
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

void	_open_all_outfile(t_cmd_lst *node)
{
	int		i;
	int		fd;

	i = 0;
	while (i < node->redir_nbr - 1)
	{
		if (node->redir_type[i] == 1 || node->redir_type[i] == 2)
		{
			fd = open(node->file[i], O_CREAT | O_RDWR, 0644);
			_handler_errors_outfiles(node, node->file[i]);
			node->redir_fd[node->index_fd] = fd;
			node->index_fd++;
			if (fd > 0)
				close (fd);
		}
		i++;
	}
}
