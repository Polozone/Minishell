/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollz_forge.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:02:17 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/27 11:02:34 by mgolinva         ###   ########.fr       */
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
			|| (line[i] == '$' && line[i + 1] != '?' && ft_isalnum(line[i + 1]) == false))
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
