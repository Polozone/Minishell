/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:29:27 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/26 17:48:23 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	ft_empty_pipe(char	*line)
{
	int		i;
	t_bool	empty_pipe;

	i = 0;
	empty_pipe = false;
	while (line[i])
	{
		if (line[i] == '|' && empty_pipe == false)
			empty_pipe = true;
		else if ((line[i] != ' ' && line[i] != '|' && line[i] != '<')
			&& (line[i] != '>'))
			empty_pipe = false;
		else if (line [i] == '<' || line[i] == '>')
			empty_pipe = true;
		else if (line[i] == '|' && empty_pipe == true)
		{
			return (true);
		}
		i ++;
	}
	if (line[i - 1] == '|' || line[0] == '|')
		empty_pipe = true;
	return (empty_pipe);
}

static t_bool	ft_too_many_pipe(char	*line)
{
	int			pipe_ct;
	int			i;
	t_var_quote	quote;

	pipe_ct = 0;
	i = 0;
	while (line[i])
	{
		ft_is_in_quote(line, i, &quote);
		if (line[i] == '|' && quote == not_in_quote)
			pipe_ct ++;
		if (line[i] != '|')
			pipe_ct = 0;
		if (pipe_ct > 1)
			return (true);
		i ++;
	}
	return (false);
}

static t_bool	ft_quote_error(char *line)
{
	int			i;
	int			ct[2];
	t_var_quote	quote;

	i = 0;
	ct[0] = 0;
	ct[1] = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			if (line[i] == '\"' && ft_is_in_quote(line, i, &quote) == false)
				ct[0] += 1;
			else if (line[i] == '\''
				&& ft_is_in_quote(line, i, &quote) == false)
				ct[1] += 1;
		}
		i ++;
	}
	if (ct[0] % 2 != 0)
		return (ft_syntax_error_print(QUOTE_ERROR));
	if (ct[1] % 2 != 0)
		return (ft_syntax_error_print(QUOTE_ERROR));
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
	else if (ft_too_many_pipe(prg->line) == true)
		error = ft_syntax_error_print(PIPE_CHEV_ERROR);
	else if (ft_empty_pipe(prg->line) == true)
		error = ft_syntax_error_print(PIPE_CHEV_ERROR);
	else if (ft_quote_error(prg->line) == true)
		error = true;
	if (error == true)
		return (true);
	return (false);
}
