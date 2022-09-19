/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:42:34 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/27 16:10:29 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int g_error;

static t_cmd_lst	*ft_create_cmd_lst(t_prg *prg)
{
	int	i;

	prg->cmd_list = ft_lstnew_cmd_list();
	i = 1;
	while (i < prg->cmd_nbr)
	{
		ft_add_back_cmd_list(&prg->cmd_list, ft_lstnew_cmd_list());
		i ++;
	}
	return (prg->cmd_list);
}

void	ft_parse(t_prg *prg)
{
	int i = 0;
	prg->cells = 0;
	if (prg->line == NULL)
		return;
	prg->line_len = ft_strlen(prg->line);
	if (ft_syntax_error(prg) == true)
	{
		g_error = 258;
		return;		
	}
	prg->cells = ft_split(prg->line, '|');
	prg->cmd_nbr = ft_array_len(prg->cells);
	prg->cmd_list = ft_create_cmd_lst(prg);
	ft_fill_cmd_lst(prg);
	// ft_builtin_args(prg);
}