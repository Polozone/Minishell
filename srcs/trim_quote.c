/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:17:29 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/18 14:38:04 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_extracted_phrase(char *line, int index, t_var_quote quote)
{
	int		start;
	int		end;
	char	*phrase;

	start = index + 1;
	end = index - 1;
	while (--start >= 0)
	{
		if (quote == in_double && line[start] == '\"')
			break;
		else if (quote == in_single && line[start] == '\'')
			break;
		else if (quote == not_in_quote && line[start] == ' ')
			break;
	}
	while (line[++end])
	{
		if (quote == in_double && line[end] == '\"')
			break;
		else if (quote == in_single && line[end] == '\'')
			break;
		else if (quote == not_in_quote && line[end] == ' ')
			break;
	}
	return (ft_substr(line, start + 1, end - (start + 1)));
}

int	ft_go_to_end_of_phrase(char *line, int index, t_var_quote quote)
{
	while (line[index + 1])
	{
		if (quote == in_double && line[index] == '\"')
			break;
		else if (quote == in_single && line[index] == '\'')
			break;
		else if (quote == not_in_quote && line[index] == ' ')
			break;
		index ++;
	}
	return (index);
}

char	*ft_trim_quote(char *line)
{
	int			i;
	char		*new_line;
	t_var_quote	quote;

	i = 0;
	new_line = ft_strdup("");
	while (line[i] && ft_is_in_quote(line, i, &quote))
	{
		if (quote == in_double)
		{
			new_line = ft_join_shrtct(new_line, ft_extracted_phrase(line, i, quote));
			i = ft_go_to_end_of_phrase(line, i, quote);
		}
		if (quote == in_single)
		{
			new_line = ft_join_shrtct(new_line, ft_extracted_phrase(line, i, quote));
			i = ft_go_to_end_of_phrase(line, i, quote);
		}
		if (quote == not_in_quote)
		{
			new_line = ft_join_shrtct(new_line, ft_extracted_phrase(line, i, quote));
			i = ft_go_to_end_of_phrase(line, i, quote);
		}
		i ++;
	}
	return (new_line);
}