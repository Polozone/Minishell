/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:06:40 by mgolinva          #+#    #+#             */
/*   Updated: 2022/10/05 11:05:09 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_mega_if(char *cmd, int i, int j)
{
	if ((i + j < ft_strlen(cmd))
		&& (cmd[i + j + 1] == ' ' || cmd[i + j + 1] == '|' || cmd[i
				+ j + 1] == 0 || cmd[i + j + 1] == 34 || cmd[i + j + 1] == 39))
	{
		if ((i > 0)
			&& (cmd[i - 1] != ' ' && cmd[i - 1] != 34
				&& cmd[i - 1] != 39 && cmd[i - 1] != '/'))
			return (0);
		return (&cmd[i]);
	}
	return (0);
}

static char	*ft_builtin_strstr(char *cmd, char *to_find)
{
	int	i;
	int	j;

	i = -1;
	if (to_find[0] == 0 || cmd == NULL)
		return (cmd);
	while (cmd[++i])
	{
		j = -1;
		while ((cmd[i + ++j] && cmd[i + j] == to_find[j])
			|| (cmd[i + j] && cmd[i + j] == to_find[j] - 32))
		{
			if (to_find[j + 1] == '\0')
			{
				if (ft_mega_if(cmd, i, j) == 0)
					return (0);
				else
					return (&cmd[i]);
			}
		}
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
