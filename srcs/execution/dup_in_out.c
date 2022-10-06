/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_in_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:26:37 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/06 09:31:14 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

void	_handler_errors_infiles(t_cmd_lst	*node, int index)
{
	if (errno == EACCES)
	{
		ft_putstr_fd(node->file[index], 2);
		write(2, ": Permission denied\n", 20);
		exit (1);
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd(node->file[index], 2);
		write(2, ": No such file or directory\n", 28);
		exit (1);
	}
	else if (access(node->file[index], R_OK) == -1)
	{
		ft_putstr_fd(node->file[index], 2);
		write(2, ": Permission denied\n", 20);
		exit (1);
	}
	else if (is_file(node->file[index]))
	{
		ft_putstr_fd(node->file[index], 2);
		write(2, ": Is a directory\n", 17);
		exit (1);
	}
}

void	_handler_errors_outfiles(t_cmd_lst	*node, char *name)
{
	if (errno == EACCES)
	{
		ft_putstr_fd(name, 2);
		write(2, ": Permission denied\n", 20);
		exit (1);
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd(name, 2);
		write(2, ": No such file or directory\n", 28);
		exit (1);
	}
	else if (is_file(name))
	{
		ft_putstr_fd(name, 2);
		write(2, ": stdin: Is a directory\n", 25);
		exit (1);
	}
	else if (access(name, W_OK) == -1)
	{
		ft_putstr_fd(name, 2);
		write(2, ": Permission denied\n", 20);
		exit(1);
	}
}

void	_set_dup_infile(t_prg *data, t_cmd_lst *node)
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
		if (dup2(node->infile, 0) == -1)
			_ft_free_and_exit(data);
		if (node->infile > 0)
			close(node->infile);
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
			_handler_errors_outfiles(node, node->file[_last_outfile(node)]);
		node->redir_fd[node->index_fd] = node->outfile;
		node->index_fd++;
		if (dup2(node->outfile, 1) == -1)
			_ft_free_and_exit(data);
		if (node->outfile > 0)
			close (node->outfile);
	}
}
