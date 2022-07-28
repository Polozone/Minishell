/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 08:49:07 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/28 10:19:16 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_find_path(t_prg *prg, t_cmd_lst *cmd_list)
{
	int		i;
	char	*path;

	i = 0;
	if (access(cmd_list->cmd_and_dep[0], F_OK) == 0)
	{
		cmd_list->path = ft_strdup(cmd_list->cmd_and_dep[0]);
		return ;
	}
	while (prg->path_list[i])
	{
		path = ft_strjoin_backslash(prg->path_list[i], cmd_list->cmd_and_dep[0]); 
		if (access(path, F_OK) == 0)
		{
			cmd_list->path = path;
			return ;
		}
		free(path);
		i ++;
	}
	cmd_list->path = NULL;
}

static void ft_fill_cmd_and_dep(t_cmd_lst *cmd_lst, char **line_split, t_token *line_token)
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
		if (line_token[i] == none)
			cmd_dep_ct ++;
	cmd_lst->cmd_and_dep = malloc ((cmd_dep_ct + 1) * sizeof(char *));
	i = -1;
	while (line_split[++i])
	{
		if (line_token[i] == none)
		{
			cmd_lst->cmd_and_dep[j] =  ft_strdup(line_split[i]);
			j ++;
		}
	}
	cmd_lst->cmd_and_dep[j] = 0;
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
	ft_find_path(prg, cmd_lst);
	ft_fill_file(cmd_lst, line_split, line_token, split_len);
	ft_is_cmd_builtin(prg, cmd_lst);
	ft_redir_assignation(prg, cmd_lst, line_token, line_split);
	ft_free_char_array(line_split);
	free(line_token);
}