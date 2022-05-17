/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Path_list_maker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:17:55 by mgolinva          #+#    #+#             */
/*   Updated: 2022/05/04 11:14:02 by mgolinva         ###   ########.fr       */
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

char	**ft_path_list_maker(char **envp, t_prg *prg)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	len = ft_array_len(envp);
	while (envp[++i])
		if (ft_strstr(envp[i], "PATH="))
			break ;
	if (i == len)
	{
		ft_putstr_fd("PATH env var is unset, no shell command will work.\n", 2);
		prg->is_there_path = false;
	}
	prg->is_there_path = true;
	j = 0;
	while (envp[i][j])
	{
		if (envp[i][j] == '=')
		{
			j ++;
			break ;
		}
		j ++;
	}
	return (ft_split(&envp[i][j], ':'));
}