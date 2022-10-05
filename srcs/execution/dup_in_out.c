/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_in_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:26:37 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/05 13:45:05 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

void	_set_dup_infile(t_cmd_lst *node)
{
	if ((_is_infile(node)))
	{
		node->infile = open(node->file[_last_infile(node) - 1], O_RDWR);
		node->redir_fd[node->index_fd] = node->infile;
		node->index_fd++;
		if (node->infile == -1)
		{
			if (is_file(node->file[_last_infile(node) - 1]))
			{
				write(2, node->cmd_and_dep[0], ft_strlen(node->cmd_and_dep[0]));
				write(2, ": -: Is a directory\n", 20);
			}
			else
			{
				ft_putstr_fd(node->file[_last_infile(node) - 1], 2);
				write(2, ": No such file or directory\n", 28);
			}
			exit(0);
		}
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
			exit (0);
		node->redir_fd[node->index_fd] = node->outfile;
		node->index_fd++;
		if (is_file(node->file[_last_outfile(node)]))
		{
			ft_putstr_fd(node->file[_last_outfile(node)], 2);
			write(2, ": -: Is a directory\n", 20);
			exit (0);
		}
		if (dup2(node->outfile, 1) == -1)
		{
			perror("");
			exit (0);
		}
	}
}
