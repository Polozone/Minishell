/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:17:29 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/22 15:59:02 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_go_to_end_of_phrase(char *line, int index, t_var_quote quote)
{
	while (line[index + 1])
	{
		if (quote == in_double && line[index] == '\"')
			break ;
		else if (quote == in_single && line[index] == '\'')
			break ;
		else if (quote == not_in_quote && line[index] == ' ')
			break ;
		index ++;
	}
	return (index);
}

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
			break ;
		else if (quote == in_single && line[start] == '\'')
			break ;
		else if (quote == not_in_quote && line[start] == ' ')
			break ;
	}
	while (line[++end])
	{
		if (quote == in_double && line[end] == '\"')
			break ;
		else if (quote == in_single && line[end] == '\'')
			break ;
		else if (quote == not_in_quote && line[end] == ' ')
			break ;
	}
	return (ft_substr(line, start + 1, end - (start + 1)));
}

char	*ft_trim_quote(char *line)
{
	int			i;
	int			last_stop;
	char		*new_line;
	t_var_quote	quote;

	i = 0;
	new_line = ft_strdup("");
	while (line[i])
	{
		ft_is_in_quote(line, i, &quote);
		if ((line[i] == '\'' || line[i] == '\"')
			&& (quote == not_in_quote))
				;
		else
			new_line = ft_join_shrtct(new_line, ft_substr(line, i, 1));
		i ++;
	}
	return (new_line);
}

void	ft_quote_trimer(t_prg *prg, t_cmd_lst *buff)
{
	int			i;
	char		*line_buff;
	t_cmd_lst	*tmp;

	i = 0;
	tmp = buff;
	line_buff = NULL;
	i = -1;
	while (tmp->cmd_and_dep[++i])
	{
		line_buff = tmp->cmd_and_dep[i];
		tmp->cmd_and_dep[i] = ft_trim_quote(tmp->cmd_and_dep[i]);
		free(line_buff);
	}
	i = -1;
	while (tmp->file[++i])
	{
		line_buff = tmp->file[i];
		tmp->file[i] = ft_trim_quote(tmp->file[i]);
		free(line_buff);
	}
}
