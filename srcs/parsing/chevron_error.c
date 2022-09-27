/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:29:03 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/22 10:46:28 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	ft_discontinuous_chevron(char *line, char chevron,
char chev_two)
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

static t_bool	ft_scovron_one(char *line, char chevron, char chev_two)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != chevron && line[i] != chev_two)
			return (false);
		i ++;
	}
	return (ft_syntax_error_print(PIPE_CHEV_ERROR));
}

static t_bool	ft_scovron_two(char *line, char c, char c_d, t_var_quote quote)
{
	int	i;
	int	chev_ct;

	i = -1;
	while (line[++i])
	{
		chev_ct = 0;
		while ((line[i])
			&& (line[i] == c || line[i] == c_d || line[i] == ' '))
		{
			if ((line[i] == c || line[i] == c_d)
				&& (ft_is_in_quote(line, i, &quote) != true))
				chev_ct ++;
			i ++;
			if (i == ft_strlen(line) && line[0] == c && chev_ct < 3)
				return (ft_scovron_one(line, c, c_d));
		}
		if (chev_ct == 3)
			return (ft_syntax_error_print(PIPE_CHEV_ERROR));
		else if (chev_ct > 3)
			return (ft_syntax_error_print(PIPE_CHEV_ERROR));
		if ((i == ft_strlen(line)) && (line[i - 1] == c || line[i - 1] == c_d))
			return (ft_syntax_error_print(PIPE_CHEV_ERROR));
	}
	return (false);
}

t_bool	ft_chevron_error(char *line, int line_len, char chevron, char che_two)
{
	int			i;
	int			chev_ct;
	t_var_quote	quote;

	i = 0;
	if (ft_scovron_two(line, chevron, che_two, quote) == true)
		return (true);
	if (ft_discontinuous_chevron(line, chevron, che_two) == true)
		return (ft_syntax_error_print(PIPE_CHEV_ERROR));
	return (false);
}
