/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:15:21 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/13 12:46:13 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

int	_parsing_exit(t_cmd_lst	*node)
{
	int		i;

	i = 0;
	while (node->cmd_and_dep[1][++i])
	{
		if (node->cmd_and_dep[1][i] == '-' || node->cmd_and_dep[1][i] == '+')
			i++;
		if (!('0' <= node->cmd_and_dep[1][i] && node->cmd_and_dep[1][i] <= '9'))
		{
			ft_putstr_fd("exit\nexit: ", 2);
			ft_putstr_fd(node->cmd_and_dep[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (255);
		}
	}
	return (0);
}

int	ft_isalpha(char	*str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((65 <= str[i] && str[i] <= 90) || (97 <= str[i] && str[i] <= 122))
			return (1);
		i++;
	}
	return (0);
}

int	_exit_builtins(t_cmd_lst *node, int i, int len, long long exit_value)
{
	if (!node->cmd_and_dep[1])
	{
		write(1, "exit\n", 5);
		exit (0);
	}
	len = ft_strlen_2d(node->cmd_and_dep);
	if (len > 2 && ft_isalpha(node->cmd_and_dep[1]) == 0)
	{
		write(2, "exit\nexit: too many arguments\n", 30);
		g_error = 1;
		return (-1);
	}
	if (_parsing_exit(node))
		exit (255);
	write(2, "exit\n", 5);
	exit_value = ft_atol(node->cmd_and_dep[1]);
	if (!checker_lli(node->cmd_and_dep[1]) || ft_isalpha(node->cmd_and_dep[1]))
	{
		write(2, node->cmd_and_dep[1], ft_strlen(node->cmd_and_dep[1]));
		write(2, ": numeric argument required\n", 28);
		exit (255);
	}
	return ((unsigned char)exit_value);
}
