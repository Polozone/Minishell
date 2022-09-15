/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollz.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:24:53 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/15 20:13:46 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
static char	*ft_get_var_name(char *line, int index)
{
	int	i;

	i = index + 1;
	while (line[i])
	{
		if (line[i] == '$' || line[i] == 34 || line[i] == 39)
		{
			i --;
			break;
		}
		else if (ft_isalnum(line[i]) == false && line[i] != '_')
		{
			i --;
			break;
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
		if (line[i] != '$' || quote == in_single)
		{
			if ((quote == not_in_quote)
			&& (line[i] == '\'' || line[i] == '\"'))
				;
			else 
				new_line = ft_join_shrtct(new_line, ft_substr(line, i, 1));
		}
		else if (line[i] == '$' && line[i + 1] >= 48 && line[i + 1] <= 57)
			i ++;
		else if (line[i] == '$')
		{
			// if (quote == in_single)
			// 	new_line = ft_join_shrtct(new_line, ft_substr(line, i, 1));
			new_line = ft_join_shrtct(new_line, ft_expend(prg, line, i));
			i ++;
			while (line[i] && ft_isalnum(line[i]) == true && line[i] != '$')
			{
				if ((line[i] == '\'' || line[i] == '\"')
				&& (ft_is_in_quote(line, i, &quote) != true))
					break;
				i ++;
			}
			i --;
		}
		if (line[i])
			i ++;
		// printf("fin de boucle I = %d, line[%d] = %c\n",i,i,line[i]);
	}
	return(new_line);
}