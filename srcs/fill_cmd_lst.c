/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:42:27 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/13 17:26:20 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*ft_get_cmd_and_dep(t_prg *prg)
{
	t_cmd_lst *buff;

	buff = prg->cmd_list;

}*/

int		ft_find_end_of_word(char *line, int start)
{
	int	i;

	i = start;
	while (line[i] != ' ')
		i ++;
	return (i);
}

void	ft_fill_cmd_and_dep(t_prg *prg)
{
	int		i;
	int		end;
	char	*word;

	i = 0;
	end = 0;
	while (prg->line[i])
	{
		if (prg->line[i] != ' ')
		{
			end = ft_find_end_of_word(prg->line, i);
			word = ft_substr(prg->line, i, end);
			if (ft_is_cmd = true)
		}
	}
}

void	ft_create_path_list(t_prg *prg)
{
	t_env_lst *buff;

	buff = prg->env_lst;
	while (buff != 0)
	{
		if (ft_strncmp(buff->name, "PATH=", 5) == 0)
		{
			prg->is_there_path = true;
			break;
		}
		prg->is_there_path = false;
	}
	if (prg->is_there_path == true)
		prg->path_list = ft_split(buff->content, ':');
}

void	ft_fill_cmd_lst(t_prg *prg)
{
	ft_create_path_list(prg);
	ft_fill_cmd_and_dep(prg);
	ft_is_cmd_builtin(prg);
	//ft_get_cmd_and_dep(prg);
	ft_redir_assignation(prg);
}
