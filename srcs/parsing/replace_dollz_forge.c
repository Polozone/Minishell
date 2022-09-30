/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollz_forge.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:02:17 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/30 17:18:40 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_forge_new_line(t_prg *prg, char *line)
{
	int			i;
	char		*new_line;
	t_var_quote	quote;

	i = 0;
	new_line = ft_strdup("");
	while (line[i])
	{
		ft_is_in_quote(line, i, &quote);
		if ((line[i] != '$' || quote == in_single)
			|| (line[i] == '$' && ft_is_phrase_a_file(line, i, quote) == true)
			|| (line[i] == '$' && line[i + 1] != '?'
				&& ft_isalnum(line[i + 1]) == false))
			ft_add_c_to_nl(quote, &new_line, line, i);
		else if (line[i] == '$' && line[i + 1] >= 48 && line[i + 1] <= 57)
			i ++;
		else if (line[i] == '$')
			i = ft_char_is_dollz(prg, line, &new_line, i);
		if (line[i])
			i ++;
	}
	return (new_line);
}

int	ft_char_is_dollz_heredoc(t_prg *prg, char *line, char **new_line, int i)
{
	t_var_quote	quote;

	while (line[i + 1] == '$' || line[i + 1] == 0)
	{
		*new_line = ft_join_shrtct(*new_line, ft_substr(line, i, 1));
		i ++;
		if (line[i] == 0)
			return (i);
	}
	*new_line = ft_join_shrtct(*new_line, ft_expend(prg, line, i));
	i ++;
	while (line[i] && ft_isalnum(line[i]) == true && line[i] != '$')
		i ++;
	if (line[i] == '?')
		;
	else
		i --;
	return (i);
}

char	*ft_forge_new_line_heredoc(t_prg *prg, char *line)
{
	int			i;
	char		*new_line;
	t_var_quote	quote;

	i = 0;
	new_line = ft_strdup("");
	while (line[i])
	{
		ft_is_in_quote(line, i, &quote);
		if ((line[i] != '$')
			|| (line[i] == '$' && ft_is_phrase_a_file(line, i, quote) == true)
			|| (line[i] == '$' && line[i + 1] != '?'
				&& ft_isalnum(line[i + 1]) == false))
			ft_add_c_to_nl(quote, &new_line, line, i);
		else if (line[i] == '$' && line[i + 1] >= 48 && line[i + 1] <= 57)
			i ++;
		else if (line[i] == '$')
			i = ft_char_is_dollz_heredoc(prg, line, &new_line, i);
		if (line[i])
			i ++;
	}
	// new_line = ft_join_shrtct(new_line, ft_strdup("\n"));
	return (new_line);
}
