/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:42:34 by mgolinva          #+#    #+#             */
/*   Updated: 2022/10/10 16:01:49 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

static t_cmd_lst	*ft_create_cmd_lst(t_prg *prg)
{
	int	i;

	prg->cmd_list = ft_lstnew_cmd_list();
	i = 1;
	while (i < prg->cmd_nbr)
	{
		ft_add_back_cmd_list(&prg->cmd_list, ft_lstnew_cmd_list());
		i++;
	}
	return (prg->cmd_list);
}

static void	ft_heredoc_counter(t_prg *prg)
{
	t_cmd_lst	*cmd_lst;

	cmd_lst = prg->cmd_list;
	prg->heredoc_nbr = 0;
	while (cmd_lst)
	{
		prg->heredoc_nbr += (ft_array_len(cmd_lst->heredoc_delimiter));
		cmd_lst = cmd_lst->next;
	}
}

void	ft_parse(t_prg *prg)
{
	int	i;

	i = 0;
	prg->cells = 0;
	if (prg->line == NULL)
		return ;
	prg->line_len = ft_strlen(prg->line);
	prg->cells = ft_split(prg->line, '|');
	prg->cmd_nbr = ft_array_len(prg->cells);
	prg->cmd_list = ft_create_cmd_lst(prg);
	ft_fill_cmd_lst(prg);
	ft_heredoc_counter(prg);
}
