/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Path_list_maker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:17:55 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/13 16:26:09 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_array_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i ++;
	return (i);
}

char	**ft_path_list_maker(t_prg *prg)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	len = ft_array_len(prg->envp);
	while (prg->envp[++i])
		if (ft_strstr(prg->envp[i], "PATH="))
			break ;
	if (i == len)
	{
		prg->is_there_path = false;
		return (0);
	}
	prg->is_there_path = true;
	j = 0;
	while (prg->envp[i][j])
	{
		if (prg->envp[i][j] == '=')
		{
			j ++;
			break ;
		}
		j ++;
	}
	return (ft_split(&prg->envp[i][j], ':'));
}