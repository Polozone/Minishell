/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:42:34 by mgolinva          #+#    #+#             */
/*   Updated: 2022/05/13 16:36:55 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_init(t_prg *prg)
{
	prg->path = 0;
	prg->cells = 0;
	prg->cmd_list = 0;
	prg->is_cmd_builtin = 0;
}

static void	ft_create_cmd_lst(t_prg *prg)
{
	int	i;

	i = 0;
	prg->cmd_list = malloc((ft_array_len(prg->cells) + 1) * sizeof(prg->cmd_list));
	while (i < ft_array_len(prg->cells))
	{
		prg->cmd_list[i] = ft_split(prg->cells[i], ' ');
		i ++;
	}
	prg->cmd_list[i] = 0;
}

void	ft_parse(t_prg *prg)
{
	ft_init(prg);
	if (prg->line == NULL)
		return;
	prg->line_len = ft_strlen(prg->line);
	if (ft_pipe_error(prg->line, prg->line_len) == true)
		return;
	prg->path = ft_path_list_maker(prg->env_p, prg);
	prg->cells = ft_split(prg->line, '|');
	prg->cmd_nbr = ft_array_len(prg->cells);
	// printf("cmd_nbr = %d\n", prg->cmd_nbr);
	ft_create_cmd_lst(prg);
	ft_is_cmd_builtin(prg);
	// ft_builtin_args(prg);
}