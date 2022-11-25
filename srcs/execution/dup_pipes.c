/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:29:05 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/10 16:17:37 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

void	_redir_first_cmd(t_cmd_lst	*node, t_prg *data)
{
	if (_is_infile(node))
		_set_dup_infile(data, node);
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
		_set_dup_infile(data, node);
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
		_set_dup_infile(data, node);
	else
		dup2(data->pipe[(node->index - 1) * 2], 0);
	if (_is_outfile(node))
	{
		_set_dup_outfile(node, data);
	}
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

int	check_launch_env(t_prg *data, t_cmd_lst *node)
{
	if (node->cmd_and_dep[1])
	{
		if (ft_strcmp(node->cmd_and_dep[1], "#") == 0)
		{
			g_error = 0;
			_print_env(data->env_lst);
			exit (g_error);
		}
		ft_putstr_fd(node->cmd_and_dep[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_error = 127;
		exit (g_error);
	}
	else
		return (1);
}
