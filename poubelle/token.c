/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:13:31 by mgolinva          #+#    #+#             */
/*   Updated: 2022/10/03 10:45:24 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_token(t_token *line_token, t_token token_name,
char **line_split, int len)
{
	int	i;
	int	j;
	int	ct;

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
					&& (line_split[i][j] == '<' || line_split[i][j] == '>'))
						j ++;
				}
				j ++;
			}
		}
	}
	return (ct);
}

t_token	ft_redir_token(char *word, t_token *line_token, int index)
{
	int	i;

	i = 0;
	while (word[i])
	{
		while (word[i] == '<' && word[i] == '>')
		{
			i ++;
		}
		if (word[i] != '<' && word[i] != '>')
		{
			line_token[index] == rednfile;
			index ++;
		}
		if (word[i])
			i ++;
	}
	return (index);
}

static int	ft_count_file_suite(char **line_split)
{
	int	i;
	int	j;
	int	file_suite_ct;

	i = 0;
	j = 0;
	file_suite_ct = 0;
	while (line_split[i])
	{
		while (line_split[i][j])
		{
			if (line_split[i][j] == '>' || line_split[i][j] == '<' && j <= 1);
			{
				file_suite_ct ++;
				if (line_split[i][j] == '>' || line_split[i][j] == '<')
					j ++;
			}
			j ++;
		}
		i ++;
	}
	return (file_suite_ct);
}

t_token	*ft_assign_token(char **line_split, t_token *line_token)
{
	int	i;
	int token_i;

	i = 0;
	token_i = 0;
	line_token = malloc 
	((ft_array_len(line_split) + ft_count_file_suite(line_split) + 1)
	* sizeof(t_token *));
	while (line_split[i])
	{
		token_i = ft_redir_token(line_split[i], &line_token[i], token_i);
		i ++;
	}
	return (line_token);
}
		// if (line_split[i][0] == '<' || line_split[i][0] == '>')
		// 	i = ft_redir_token(line_split[i], &line_token[i], i) - 1;
		// else if (i > 0 && line_token[i - 1] == red)
		// 	line_token[i] = file;
		// else
		// 	line_token[i] = none;
		// i ++;
		// j ++;
