/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_in_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:26:37 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/05 17:16:47 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

int	_handler_errors_infiles(t_cmd_lst	*node, int index)
{
	ft_putstr_fd(node->file[index], 2);
	if (errno == EACCES)
		write(2, ": Permission denied\n", 20);
	else if (errno == ENOENT)
		write(2, ": No such file or directory\n", 28);
	else if (access(node->file[index], R_OK) == -1)
	{
		write(2, ": Permission denied\n", 20);
		exit (1);
	}
	else if (is_file(node->file[index]))
		write(2, ": stdin: Is a directory\n", 25);
	exit(1);
}

int	_handler_errors_outfiles(t_cmd_lst	*node)
{
	ft_putstr_fd(node->file[_last_outfile(node)], 2);
	if (errno == EACCES)
		write(2, ": Permission denied\n", 20);
	else if (errno == ENOENT)
		write(2, ": No such file or directory\n", 28);
	else if (is_file(node->file[_last_outfile(node)]))
	{
		write(2, ": stdin: Is a directory\n", 25);
		exit (1);
	}
	else if (access(node->file[_last_outfile(node)], W_OK) == -1)
		write(2, ": Permission denied\n", 20);
	exit(1);
}

void	_set_dup_infile(t_cmd_lst *node)
{
	int	index;

	if ((_is_infile(node)))
	{
		index = _last_infile(node) - 1;
		node->infile = open(node->file[index], O_RDWR);
		node->redir_fd[node->index_fd] = node->infile;
		node->index_fd++;
		if (node->infile == -1)
			_handler_errors_infiles(node, index);
		else
		{
			if (dup2(node->infile, 0) == -1)
				exit (0);
		}
	}
}

void	_set_dup_outfile(t_cmd_lst *node, t_prg *data)
{
	if (_is_outfile(node))
	{
		_open_all_outfile(node);
		if (node->redir_type[_last_outfile(node)] == 2)
			node->outfile = open(node->file[_last_outfile(node)], O_CREAT
					| O_RDWR | O_APPEND, 0644);
		else if (node->redir_type[_last_outfile(node)] == 1)
			node->outfile = open(node->file[_last_outfile(node)], O_CREAT
					| O_RDWR | O_TRUNC, 0644);
		if (node->outfile == -1)
			_handler_errors_outfiles(node);
		node->redir_fd[node->index_fd] = node->outfile;
		node->index_fd++;
		if (dup2(node->outfile, 1) == -1)
			_ft_free_and_exit(data);
	}
}
