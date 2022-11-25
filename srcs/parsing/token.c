/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:13:31 by mgolinva          #+#    #+#             */
/*   Updated: 2022/10/10 16:25:24 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	ft_ct_fl_st(char **line_split)
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
			if ((line_split[i][j] == '>' || line_split[i][j] == '<')
				&& (j <= 1))
			{
				if (line_split[i][j + 1] == '>' || line_split[i][j +1] == '<')
					j ++;
				file_suite_ct ++;
			}
			j ++;
		}
		i ++;
	}
	return (file_suite_ct);
}

t_bool	ft_ghetto(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '<' || word[i] == '>')
			return (true);
		i ++;
	}
	return (false);
}

t_token	ft_assign_rdnfile(char **split, int i)
{
	char	*buf;

	buf = split[i - 1];
	split[i - 1] = ft_strdup(buf);
	split[i] = ft_join_shrtct(buf, split[i]);
	return (rednfile);
}

t_token	*ft_assign_token(char **split, t_token *line_token, int i)
{
	i = -1;
	line_token = malloc((ft_array_len(split) + ft_ct_fl_st(split) + 1) * 8);
	if (line_token == NULL)
		exit (1);
	while (split[++i])
	{
		if (split[i][0] == '<' || split[i][0] == '>')
			line_token[i] = ft_redir_token(split[i]);
		else if (i > 0 && line_token[i - 1] == red)
		{
			if (ft_ghetto(split[i]) == true)
				line_token[i] = ft_assign_rdnfile(split, i);
			else
				line_token[i] = file;
		}
		else
		{
			if (ft_ghetto(split[i]) == true)
				line_token[i] = cmdnredirnfile;
			else
				line_token[i] = none;
		}
	}
	return (line_token);
}
