/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:42:27 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/21 09:46:07 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_create_path_list(t_prg *prg)
{
	t_env_lst	*buff;

	buff = prg->env_lst;
	while (buff != 0)
	{
		if (ft_strncmp(buff->name, "PATH", 5) == 0)
		{
			prg->is_there_path = true;
			break ;
		}
		buff = buff->next;
		prg->is_there_path = false;
	}
	if (prg->is_there_path == true)
		prg->path_list = ft_split(buff->content, ':');
}

t_bool	ft_is_there_dollzzz(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (true);
		i ++;
	}
	return (false);
}

void	ft_expend_env_variable(t_prg *prg, t_cmd_lst *cmd_lst)
{
	int		i;
	char	*buff;

	i = 0;
	if (prg->cells == 0)
		return ;
	while (prg->cells[i])
	{
		if (ft_is_there_dollzzz(prg->cells[i]) == true)
		{
			buff = prg->cells[i];
			prg->cells[i] = ft_forge_new_line(prg, prg->cells[i]);
			free(buff);
		}
		i ++;
	}
}

void	ft_fill_cmd_lst(t_prg *prg)
{
	int			i;
	t_cmd_lst	*buff;

	i = 0;
	buff = prg->cmd_list;
	ft_create_path_list(prg);
	while (buff != NULL && prg->cells[i])
	{
		ft_expend_env_variable(prg, buff);
		ft_fill_node(prg->cells[i], buff, prg);
		ft_quote_trimer(prg, buff);
		ft_find_path(prg, buff);
		i ++;
		buff = buff->next;
	}
	if (prg->path_list != NULL)
		ft_free_char_array(prg->path_list);
	prg->path_list = NULL;
}
