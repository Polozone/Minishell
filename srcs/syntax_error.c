/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:29:27 by mgolinva          #+#    #+#             */
/*   Updated: 2022/05/18 14:19:40 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_bool	ft_printf_error(int mode)
{

	if (mode == ONE_PIPE)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (true);
	}
	else if (mode == TWO_PIPE)
	{
		ft_putstr_fd("syntax error near unexpected token `||'\n", 2);
		return (true);
	}
	else if (mode == ONE_RED)
	{
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
		return (true);
	}
	else if (mode == TWO_RED)
	{
		ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
		return (true);
	}
	return (false);
}

static t_bool	ft_pipe_error(char *line, int line_len)
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
		while (line[i] && line[i] == '|')
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

static t_bool	ft_chevron_error(char *line, int line_len)
{
	int	i;
	int	chev_ct;

	i = -1;

	if (line[0] == '>')
	{
		if (line_len > 1 && line[1] == '>')
			return (ft_printf_error(TWO_RED));
		return (ft_printf_error(ONE_RED));
	}
	while (line[++i])
	{
		chev_ct = 0;
		while (line[i] && line[i] == '>')
		{
			chev_ct ++;
			i ++;
		}
		if (chev_ct == 3)
			return (ft_printf_error(ONE_RED));
		else if (chev_ct > 3)
			return (ft_printf_error(TWO_RED));
	}
	return (false);
}

static t_bool ft_quote_error(char *line)
{
	int	i;
	int	ct;

	ct = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
			ct ++;
		i ++;
	}
	if (ct % 2 != 0)
	{
		ft_putstr_fd("syntax error, open quote\n", 2);
		return (true);
	}
	return (false);
}

t_bool	ft_syntax_error(t_prg *prg)
{
	if (ft_chevron_error(prg->line, prg->line_len) == true)
		return (true);
	if (ft_pipe_error(prg->line, prg->line_len) == true)
		return (true);
	if (ft_quote_error(prg->line) == true)
		return (true);
	return (false);
}