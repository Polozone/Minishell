/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:28:29 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/29 09:44:30 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

int	ft_error_print_one(t_cmd_lst *node, int error_code, char *error_source)
{
	if (error_code == 127) 
	// && node->heredoc_delimiter[0]
	// 	== NULL && node->cmd_and_dep[0] != NULL
	// 	&& node->is_cmd_builtin == not_built_in)
	{
		ft_putstr_fd("Minichell: ", 2);
		ft_putstr_fd(error_source, 2);
		ft_putstr_fd(": command not found\n", 2);
		g_error = 127;
	}
	if (error_code == 2)
	{
		ft_putstr_fd("Minichell: ", 2);
		ft_putstr_fd(error_source, 2);
		ft_putstr_fd(": filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);	
		g_error = 2;
	}
	return (g_error);
}
int	ft_error_print_two(t_cmd_lst *node, int error_code, char *error_source)
{
	if (error_code == 126 && node->heredoc_delimiter[0]
		== NULL && node->cmd_and_dep[0] != NULL
		&& node->is_cmd_builtin == not_built_in)
	{
		ft_putstr_fd("Minichell: ", 2);
		ft_putstr_fd(error_source, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_error = 126;
	}
	if (error_code == -126)
	{
		ft_putstr_fd("Minichell: ", 2);
		ft_putstr_fd(error_source, 2);
		ft_putstr_fd(": is a directory\n", 2);	
		g_error = 126;
	}
	return (g_error);
}

t_bool	ft_syntax_error_print(int error_code)
{
	if (error_code == PIPE_CHEV_ERROR)
	{
		ft_putstr_fd("Syntax error\n", 2);
		g_error = 258;
		return (true);
	}
	if (error_code == QUOTE_ERROR)
	{
		ft_putstr_fd("Error, open quote\n", 2);
		g_error = 258;
		return (true);
	}
	else
		return (false);
}
