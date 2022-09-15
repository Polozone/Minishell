/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollz.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:24:53 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/14 17:25:35 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_var_name(char *line, int index)
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

/*int	ft_go_to_next_word(char *line, int index)
{
	int	i;

	i = index;

}*/

char	*ft_expended_var(t_prg *prg, char *line, int index)
{
	t_env_lst	*env_lst;
	char		*var_name;
	char		*word;

	env_lst = prg->env_lst;
	var_name = ft_get_var_name(line, index);
	word = NULL;
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

char	*ft_make_word(t_prg *prg, char *line, int index, t_var_quote quote)
{
	int	i;

	i = index;
	if (quote == in_double)
	{
		while(line[i] && line[i] != '$' && line[i] != '\"')
			i ++;
		if (line[i] == '$')
			return (ft_join_shrtct(ft_substr(line, index, i - index), ft_expended_var(prg, line, i)));
	}
}

char	*ft_forge_new_line(t_prg *prg, char *line)
{
	int	i;
	t_var_quote quote;
	t_dollz_lst *word_list;

	i = 0;
	word_list = ft_lstnew_dollz_list(ft_strdup(""));
	while (line[i])
	{
		ft_is_in_quote(line, i, &quote);
		if (quote == in_double)
		{
			ft_add_back_dollz_list(&word_list, ft_lstnew_dollz_list(ft_make_word(prg, line, i, quote)));
		}
		else if (quote == in_single)
		{
		}
		else if (quote == not_in_quote)
		{
		}
		while (word_list)
		{
			printf("word = %s\n", word_list->word);
			word_list = word_list->next;
		}
		i ++;
		// i = ft_go_to_next_word();
	}
}