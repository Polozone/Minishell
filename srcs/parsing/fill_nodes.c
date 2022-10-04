/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 08:49:07 by mgolinva          #+#    #+#             */
/*   Updated: 2022/10/03 14:31:06 by mgolinva         ###   ########.fr       */
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

static char	* ft_get_dep(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '>' || word[i] == '<')
			break ;
		i ++;
	}
	return (ft_substr(word, 0, i));
}

static void	ft_fill_cmd_and_dep(t_cmd_lst *cmd_lst, char **line_split,
	t_token *line_token)
{
	int	cmd_dep_ct;
	int	i;
	int	j;
	int	len;

	i = -1;
	j = 0;
	cmd_dep_ct = 0;
	len = ft_array_len(line_split);
	while (++i < len)
		if (line_token[i] == none || line_token[i] == cmdnredirnfile)
			cmd_dep_ct ++;
	cmd_lst->cmd_and_dep = malloc((cmd_dep_ct + 1) * sizeof(char *));
	if (!cmd_lst->cmd_and_dep)
		exit (1);
	i = -1;
	while (line_split[++i])
	{
		if (line_token[i] == none)
		{
			cmd_lst->cmd_and_dep[j] = ft_strdup(line_split[i]);
			j ++;
		}
		else if (line_token[i] == cmdnredirnfile)
		{
			cmd_lst->cmd_and_dep[j] = ft_get_dep(line_split[i]);
			j ++;
		}
	}
	cmd_lst->cmd_and_dep[j] = 0;
}

void	ft_heredoc_delimiter(t_prg *prg, t_cmd_lst *cmd_lst, char **l_split)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cmd_lst->redir_nbr)
		i ++;
	cmd_lst->heredoc_delimiter = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (cmd_lst->file[i])
	{
		if (cmd_lst->redir_type[i] == heredoc)
		{
			cmd_lst->heredoc_delimiter[j] = ft_strdup(cmd_lst->file[i]);
			j ++;
		}
		i ++;
	}
	cmd_lst->heredoc_delimiter[j] = 0;
}

void	ft_fill_node(char *cell, t_cmd_lst *cmd_lst, t_prg *prg)
{
	char	**line_split;
	t_token	*line_token;
	int		split_len;
	int		i;

	i = 0;
	line_split = ft_split(cell, ' ');
	split_len = ft_array_len(line_split);
	line_token = ft_assign_token(line_split, line_token);
	ft_fill_cmd_and_dep(cmd_lst, line_split, line_token);
	ft_fill_file(cmd_lst, line_split, line_token, split_len);
	ft_is_cmd_builtin(prg, cmd_lst);
	ft_redir_assignation(prg, cmd_lst, line_token, line_split);
	ft_heredoc_delimiter(prg, cmd_lst, line_split);
	ft_free_char_array(line_split);
	free(line_token);
}
