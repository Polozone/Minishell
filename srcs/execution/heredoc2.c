/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:16:13 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/05 14:20:48 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

void	_close_pipe_hd(t_cmd_lst	*tmp, char *line, char *buf, int i)
{
	free(buf);
	if (!tmp->heredoc_delimiter[i + 1])
	{
		close(tmp->pipe_hd[0]);
		write(tmp->pipe_hd[1], line, ft_strlen(line));
		close(tmp->pipe_hd[1]);
	}
	free(line);
}

void	check_heredoc(t_cmd_lst *tmp)
{
	if (tmp->heredoc_delimiter[0])
	{
		close(tmp->pipe_hd[0]);
		close(tmp->pipe_hd[1]);
	}
}
