/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:13:31 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/21 09:46:11 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int ft_count_token(t_token *line_token, t_token token_name, char **line_split, int len)
{
	int	i;
	int j;
	int ct;

	i = -1;
	ct = 0;
	while (++i < len)
	{	
		j = 0;
		if (line_token[i] == token_name)
		{
				while (line_split[i][j])
				{
					if (line_split[i][j] == '<' || line_split[i][j] == '>')
					{
						ct ++;
						while ((line_split[i][j])
						&&(line_split[i][j] == '<' || line_split[i][j] == '>'))
							j ++;
					}
					j ++;
				}
		}
	}
	return (ct);
}

t_token	ft_redir_token(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] != '<' && word[i] != '>')
			return (rednfile);
		i ++;
	}
	return (red);
}

t_token	*ft_assign_token(char **line_split, t_token *line_token)
{
	int	i;

	i = 0;
	line_token = malloc ((ft_array_len(line_split) + 1) * sizeof(t_token *));
	while (line_split[i])
	{
		if (line_split[i][0] == '<' || line_split[i][0] == '>')
			line_token[i] = ft_redir_token(line_split[i]);
		else if (i > 0 && line_token[i - 1] == red)
			line_token[i] = file;
		else 
			line_token[i] = none;
		i ++;
	}
	return (line_token);
}