/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:29:27 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/21 15:55:56 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_bool ft_empty_pipe(char	*line)
{
	int		i;
	int		pipe_ct;
	t_bool	empty_pipe;

	i = 0;
	pipe_ct = 0;
	empty_pipe = true;
	while (line[i])
	{
		if (line[i] == '|')
			pipe_ct ++;
		if (line[i] != ' ' && line[i] != '|' && line[i] != '<' && line[i] != '>')
			empty_pipe = false;
		else if (line [i] == '<' || line[i] == '>')
			empty_pipe = true;
		else if (line[i] == '|' && empty_pipe == true)
			return (true);
		i ++;
	}
	if (pipe_ct == 0)
		return (false);
	if (line[i - 1] == '|')
		empty_pipe = true;
	return (empty_pipe);
}

// t_bool ft_is_there_chev_error(char *line, char c)
// {
// 	int	i;
// 	int char_ct;

// 	i = 0;
// 	char_ct = 0;
// 	while (line[i] && line[i] != '|')
// 	{
// 		if (line[i] == c)
// 			char_ct ++;
// 		if (line[i] != c && line[i] != ' ' && char_ct <= 2)
// 			char_ct = 0;
// 		if (char_ct > 2)
// 			return (true);
// 		i ++;
// 	}
// 	return (false);
// }

// t_bool	ft_chevron_error(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '<' && ft_is_there_chev_error(line, '<') =)
// 		{

// 		}
// 		else if (line[i] == '>')

// 		i ++;
// 	}
// }

t_bool ft_discontinuous_chevron(char *line, char chevron, char chev_two)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		if (line[i] == chev_two || line[i] == chevron)
		{
			j = i + 1;
			while (line[j] && line[j] == ' ')
			{
				j ++;
				if (line[j] == chev_two || line[j] == chevron)
					return (true);
			}
		}
		i ++;
	}
	return (false);
}

t_bool ft_scotch_chevron(char *line, char chevron)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != chevron)
			return (false);
		i ++;
	}
	return(ft_printf_error(SYNT_ER, chevron));
}

static t_bool	ft_chevron_error(char *line, int line_len, char chevron, char che_two)
{
	int			i;
	int			chev_ct;
	t_var_quote	quote;

	i = 0;
	while (line[i])
	{
		chev_ct = 0;
		while ((line[i])
		&& (line[i] == chevron || line[i] == che_two || line[i] == ' '))
		{
			if ((line[i] == chevron || line[i] == che_two) 
			&& (ft_is_in_quote(line, i, &quote) != true))
				chev_ct ++;
			i ++;
			if (i == line_len && line[0] == chevron &&  chev_ct < 3)
				return (ft_scotch_chevron(line, chevron));
		}
		if (chev_ct == 3)
			return (ft_printf_error(ONE_RED, chevron));
		else if (chev_ct > 3)
			return (ft_printf_error(TWO_RED, chevron));
		if ((i == line_len)
		&& (line[i - 1] == chevron || line[i - 1] == che_two))
			return (ft_printf_error(SYNT_ER, chevron));
		i ++;
	}
	if (ft_discontinuous_chevron(line, chevron, che_two) == true)
		return (ft_printf_error(SYNT_ER, chevron));
	return (false);
}

static t_bool ft_quote_error(char *line)
{
	int	i;
	int	ct[2] = {0};
	t_var_quote	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			if (line[i] == '\"' && ft_is_in_quote(line, i, &quote) == false)
				ct[0] ++;
			else if (line[i] == '\'' && ft_is_in_quote(line, i, &quote) == false)
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

t_bool	ft_syntax_error(t_prg *prg)
{
	t_bool	error;

	error = false;
	if (ft_chevron_error(prg->line, prg->line_len, '>', '<') == true)
		error = true;
	else if (ft_chevron_error(prg->line, prg->line_len, '<', '>') == true)
		error = true;
	else if (ft_empty_pipe(prg->line) == true)
	{
		ft_printf_error(SYNT_ER, 0);
		error = true;
	}
	else if (ft_quote_error(prg->line) == true)
		error = true;
	if (error == true)
		return (true);
	return (false);
}
