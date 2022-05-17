/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:29:27 by mgolinva          #+#    #+#             */
/*   Updated: 2022/05/17 11:02:56 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_bool	ft_printf_error(int mode)
{

	if (mode == ONE_PIPE)
	{
		ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
		g_error = 258;
		return (true);
	}
	if (mode == TWO_PIPE)
	{
		ft_putstr_fd(" syntax error near unexpected token `||'\n", 2);
		g_error = 258;
		return (true);
	}
	if (mode == ONE_RED)
	{
		ft_putstr_fd(" syntax error near unexpected token `>'\n", 2);
		g_error = 258;
		return (true);
	}
	if (mode == TWO_RED)
	{
		ft_putstr_fd(" syntax error near unexpected token `>>'\n", 2);
		g_error = 258;
		return (true);
	}
	return (false);
}

t_bool	ft_pipe_error(char *line, int line_len)
{
	int	i;
	int	pipe_ct;

	i = -1;

	if (line[0] == '|')
	{
		if (line_len > 1 && line[1] == '|')
			return (ft_printf_error(TWO_PIPE));
		return (ft_printf_error(ONE_PIPE));
	}
	while (line[++i])
	{
		pipe_ct = 0;
		while (line[i] == '|')
		{
			pipe_ct ++;
			i ++;
		}
		if (pipe_ct == 3)
			return (ft_printf_error(ONE_PIPE));
		else if (pipe_ct > 3)
			return (ft_printf_error(TWO_PIPE));
	}
	return (false);
}