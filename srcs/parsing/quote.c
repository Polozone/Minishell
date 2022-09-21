/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:34:01 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/21 16:28:29 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	ft_quotch(t_var_quote quote)
{
	if (quote == not_in_quote)
		return (false);
	else
		return (true);
}

t_bool	ft_is_in_quote(char *line, int index, t_var_quote *quote)
{
	int	i;

	i = -1;
	*quote = not_in_quote;
	if (index == 0 || index == ft_strlen(line) - 1)
		return (false);
	while (line[++i])
	{
		if (line[i] == '\'' && *quote == not_in_quote && i != index)
			*quote = in_single;
		else if (line[i] == '\"' && *quote == not_in_quote && i != index)
			*quote = in_double;
		else if (*quote == in_single && line[i] == '\'')
			*quote = not_in_quote;
		else if (*quote == in_double && line[i] == '\"')
			*quote = not_in_quote;
		if (i == index)
			return (ft_quotch(*quote));
	}
	if (*quote == not_in_quote)
		return (false);
	else
		return (true);
}
