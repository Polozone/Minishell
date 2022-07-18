/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:06:40 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/18 16:40:59 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_builtin_strstr(char *cmd, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[0] == 0)
		return (cmd);
	while (cmd[i])
	{
		j = 0;
		while (cmd[i + j] && cmd[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
			{
				if ((i + j < ft_strlen(cmd))
				&& (cmd[i+j+1] == ' ' || cmd[i+j+1] == '|' 
				|| cmd[i+j+1] == '\0' || cmd[i+j+1] == 34 || cmd[i+j+1] == 39))
				{
					if ((i > 0)
					&& (cmd[i - 1] != ' ' && cmd[i - 1] != 34 && cmd[i - 1] != 39 && cmd[i - 1] != '/'))
						return (0);
					return (&cmd[i]);
				}
			}
			j ++;
		}
		i ++;
	}
	return (0);
}

void	ft_is_cmd_builtin(t_prg *prg, t_cmd_lst *cmd_lst)
{
	if (ft_builtin_strstr(cmd_lst->cmd_and_dep[0], "echo") != NULL)
		cmd_lst->is_cmd_builtin = echo;
	else if (ft_builtin_strstr(cmd_lst->cmd_and_dep[0], "cd") != NULL)
		cmd_lst->is_cmd_builtin = cd;
	else if (ft_builtin_strstr(cmd_lst->cmd_and_dep[0], "pwd") != NULL)
		cmd_lst->is_cmd_builtin = pwd;
	else if (ft_builtin_strstr(cmd_lst->cmd_and_dep[0], "export") != NULL)
		cmd_lst->is_cmd_builtin = export;
	else if (ft_builtin_strstr(cmd_lst->cmd_and_dep[0], "unset") != NULL)
		cmd_lst->is_cmd_builtin = unset;
	else if (ft_builtin_strstr(cmd_lst->cmd_and_dep[0], "env") != NULL)
		cmd_lst->is_cmd_builtin = env;
	else if (ft_builtin_strstr(cmd_lst->cmd_and_dep[0], "exit") != NULL)
		cmd_lst->is_cmd_builtin = quit;
}
