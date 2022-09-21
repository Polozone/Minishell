/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollz.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:24:53 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/21 09:46:10 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_get_var_name(char *line, int index)
{
	int	i;

	i = index + 1;
	while (line[i])
	{
		if (line[i] == '$' || line[i] == 34 || line[i] == 39)
		{
			i --;
			break ;
		}
		else if (ft_isalnum(line[i]) == false && line[i] != '_')
		{
			i --;
			break ;
		}
		i ++;
	}
	if (i == 0)
		return (NULL);
	return (ft_substr(line, index + 1, i - index));
}

char	*ft_expend(t_prg *prg, char *line, int index)
{
	t_env_lst	*env_lst;
	char		*var_name;

	env_lst = prg->env_lst;
	var_name = ft_get_var_name(line, index);
	if (var_name == NULL)
		return (ft_strdup(""));
	while (env_lst != NULL)
	{
		if (ft_strcmp(env_lst->name, var_name) == 0)
		{
			free(var_name);
			return (ft_strdup(env_lst->content));
		}
		env_lst = env_lst->next;
	}
	return (ft_strdup(""));
}

t_bool	ft_is_phrase_a_file(char *line, int index, t_var_quote quote)
{
	char	*phrase;

	phrase = ft_extracted_phrase(line, index, quote);
	if (access(phrase, F_OK) == 0)
	{
		free(phrase);
		return (true);
	}
	free(phrase);
	return (false);
}

int	ft_char_is_dollz(t_prg *prg, char *line, char **new_line, int i)
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
	{
		if ((line[i] == '\'' || line[i] == '\"')
			&& (ft_is_in_quote(line, i, &quote) != true))
			break ;
		i ++;
	}
	i --;
	return (i);
}

void	ft_add_c_to_nl(t_var_quote quote, char **new_line, char *line, int i)
{
	if ((quote == not_in_quote)
		&& (line[i] == '\'' || line[i] == '\"'))
		;
	else
		*new_line = ft_join_shrtct(*new_line, ft_substr(line, i, 1));
}

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
			|| (line[i] == '$' && ft_isalnum(line[i + 1]) == false))
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
			// while (line[i + 1] == '$' || line[i + 1] == 0)
			// {
			// 	new_line = ft_join_shrtct(new_line, ft_substr(line, i, 1));
			// 	i ++;
			// 	if (line[i] == 0)
			// 		return (new_line);
			// }
			// new_line = ft_join_shrtct(new_line, ft_expend(prg, line, i));
			// i ++;
			// while (line[i] && ft_isalnum(line[i]) == true && line[i] != '$')
			// {
			// 	if ((line[i] == '\'' || line[i] == '\"')
			// 	&& (ft_is_in_quote(line, i, &quote) != true))
			// 		break;
			// 	i ++;
			// }
			// i --;