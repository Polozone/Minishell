/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:06:40 by mgolinva          #+#    #+#             */
/*   Updated: 2022/05/12 16:18:14 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_builtin_init(t_prg *prg)
{
	int	i;

	i = 0;
	while (prg->is_cmd_builtin[i])
	{
		prg->is_cmd_builtin[i] = not_built_in;
		i ++;
	}
}

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
				&& (cmd[i + j + 1] == ' ' || cmd[i + j + 1] == '|' || cmd[i + j + 1] == '\0' || cmd[i + j + 1] == 34 || cmd[i + j + 1] == 39))
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

void	ft_is_cmd_builtin(t_prg *prg)
{
	int	i;

	i = 0;
	prg->is_cmd_builtin = malloc((prg->cmd_nbr + 1) * sizeof(prg->is_cmd_builtin));
	ft_builtin_init(prg);
	while (prg->cmd_list[i])
	{
		if (ft_builtin_strstr(prg->cmd_list[i][0], "echo") != NULL)
			prg->is_cmd_builtin[i] = echo;
		else if (ft_builtin_strstr(prg->cmd_list[i][0], "cd") != NULL)
			prg->is_cmd_builtin[i] = cd;
		else if (ft_builtin_strstr(prg->cmd_list[i][0], "pwd") != NULL)
			prg->is_cmd_builtin[i] = pwd;
		else if (ft_builtin_strstr(prg->cmd_list[i][0], "export") != NULL)
			prg->is_cmd_builtin[i] = export;
		else if (ft_builtin_strstr(prg->cmd_list[i][0], "unset") != NULL)
			prg->is_cmd_builtin[i] = unset;
		else if (ft_builtin_strstr(prg->cmd_list[i][0], "env") != NULL)
			prg->is_cmd_builtin[i] = env;
		else if (ft_builtin_strstr(prg->cmd_list[i][0], "exit") != NULL)
			prg->is_cmd_builtin[i] = quit;
		i ++;
	}
}
