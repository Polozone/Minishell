/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:29:27 by mgolinva          #+#    #+#             */
/*   Updated: 2022/06/16 11:28:22 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_bool	ft_printf_error(int mode, char chevron)
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
		printf("syntax error near unexpected token `%c'\n", chevron);
		return (true);
	}
	else if (mode == TWO_RED)
	{
		printf("syntax error near unexpected token `%c%c'\n", chevron, chevron);
		return (true);
	}
	if (mode == SYNT_ER)
	{
		ft_putstr_fd("syntax error\n", 2);
		return (true);
	}
	return (false);
}

static t_bool	ft_pipe_error(char *line, int line_len)
{
	int	i;
	int	pipe_ct;

	i = 0;
	while (line[i])
	{
		pipe_ct = 0;
		while ((line[i])
		&& (line[i] == '|' || line[i] == ' '))
		{
			if (line[i] == '|')
				pipe_ct ++;
			i ++;
			if ((i == line_len && i < 2)
			|| (line_len >  1 && line [0] == '|' && line[1] != '|'))
				return (ft_printf_error(ONE_PIPE, 0));
			else if ((i == line_len && i >= 2 && line[i - 1] == '|')
			|| (line_len > 2 && line[0] == '|' && line[1] == '|'))
				return (ft_printf_error(TWO_PIPE, 0));
		}
		if (pipe_ct == 3)
			return (ft_printf_error(ONE_PIPE, 0));
		if (pipe_ct > 3)
			return (ft_printf_error(TWO_PIPE, 0));
		else if (i == line_len && line[i] == '|')
			return (ft_printf_error(SYNT_ER, 0));
			i ++;
	}
	return (false);
}

static t_bool	ft_chevron_error(char *line, int line_len, char chevron, char che_two)
{
	int	i;
	int	chev_ct;

	i = 0;
	while (line[i])
	{
		chev_ct = 0;
		while ((line[i])
		&& (line[i] == chevron || line[i] == che_two || line[i] == ' '))
		{
			if (line[i] == chevron || line[i] == che_two)
				chev_ct ++;
			i ++;
			if (i == line_len - 1 && line[0] == chevron &&  chev_ct < 3)
				return (ft_printf_error(SYNT_ER, chevron));
		}
		if (chev_ct == 3)
			return (ft_printf_error(ONE_RED, chevron));
		else if (chev_ct > 3)
			return (ft_printf_error(TWO_RED, chevron));
		else if ((i == line_len - 1)
		&& (line[i] == chevron || line[i] == che_two))
			return (ft_printf_error(SYNT_ER, chevron));
		i ++;
	}
	return (false);
}

static t_bool ft_quote_error(char *line)
{
	int	i;
	int	ct[2] = {0};

	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			if (line[i] == 34 && ft_is_in_single(line, i) == false)
				ct[0] ++;
			else if (line[i] == 39 && ft_is_in_double(line, i) == false)
				ct[1] ++;
		}
		i ++;
	}
	if (ct[0] % 2 != 0)
	{
		ft_putstr_fd("syntax error, open quote\n", 2);
		return (true);
	}
	if (ct[1] % 2 != 0)
	{
		ft_putstr_fd("syntax error, open quote\n", 2);
		return (true);
	}
	return (false);
}

char	*ft_trim_space(char *line)
{
	int		i;
	int		j;
	int		spc_ct;
	char	*trim;

	i = 0;
	j = 0;
	spc_ct = 0;
	if (line == 0)
		return (0);
	while (line[i])
	{
		if (line[i] != ' ')
			spc_ct ++;
		i ++;
	}
	i = 0;
	trim = malloc((spc_ct + 1) * sizeof(char));
	if (!trim)
		exit (1);
	while (line[i])
	{
		if (line[i] != ' ')
		{
			trim[j] = line[i];
			j ++;
		}
		i ++;
	}
	trim[j] = 0;
	return (trim);
}
t_bool	ft_syntax_error(t_prg *prg)
{
	t_bool	error;

	error = false;
	if (ft_chevron_error(prg->line, prg->line_len, '>', '<') == true)
		error = true;
	else if (ft_chevron_error(prg->line, prg->line_len, '<', '>') == true)
		error = true;
	else if (ft_pipe_error(prg->line, prg->line_len) == true)
		error = true;
	else if (ft_quote_error(prg->line) == true)
		error = true;
	if (error == true)
		return (true);
	return (false);
}