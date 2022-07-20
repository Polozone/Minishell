/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:00:01 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/20 08:33:32 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int ft_count_redir(t_token *line_token, int split_len)
{
	int i;
	int redir_ct;

	i = 0;
	redir_ct = 0;
	while (i < split_len)
	{
		if (line_token[i] == red || line_token[i] == rednfile)
			redir_ct ++;
		i ++;
	}
	return (redir_ct);
}

static t_redir ft_redir_t_finder(t_cmd_lst *cmd_lst, char **line_split, int index)
{
	int	line_len;

	line_len = ft_strlen(line_split[index]);
	if (line_split[index][0] == '<')
	{
		if (line_len > 1 && line_split[index][1] == '<')
		{
			if (ft_array_len(line_split) > 1 && line_len == 2)
				cmd_lst->heredoc_delimiter = ft_strdup(line_split[index + 1]);
			else
				cmd_lst->heredoc_delimiter = ft_substr(line_split[index], 2, line_len);
			return (heredoc);
		}
		return (input);
	}
	else if (line_split[index][0] == '>')
	{
		if (line_len > 1 && line_split[index][1] == '>')
			return (out_append);
		return (output);
	}
	return (error);
}

void ft_redir_assignation(t_prg *prg, t_cmd_lst *cmd_lst,
t_token *line_token, char **line_split)
{
	int i;
	int red_ct;
	int	split_len;

	i = 0;
	red_ct = 0;
	split_len = ft_array_len(line_split);
	cmd_lst->redir_nbr = ft_count_redir(line_token, split_len);
	cmd_lst->redir_type = malloc(cmd_lst->redir_nbr * sizeof(t_redir));
	while (i < split_len)
	{
		if (line_token[i] == red || line_token[i] == rednfile)
		{
			cmd_lst->redir_type[red_ct] =
			ft_redir_t_finder(cmd_lst, line_split, i);
			red_ct ++;
		}
		i ++;
	}
}