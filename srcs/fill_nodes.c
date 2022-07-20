/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 08:49:07 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/20 08:53:24 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static unsigned int	ft_go_to_chev_end(char *file_name)
{
	int	i;

	i = 0;
	while (file_name[i] == '<' || file_name[i] == '>')
		i ++;
	return (i);
}

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

static void	ft_fill_cmd_and_dep(t_cmd_lst *cmd_lst, char **line_split, t_token *line_token)
{
	int	end;
	int	start;
	int	i;
	int	len;

	i = 0;
	start = 0;
	len = ft_array_len(line_split);
	while (start < len && line_token[start] != none)
		start ++;
	end = start;
	while (end < len && line_token[end] == none)
		end ++;
	cmd_lst->cmd_and_dep = malloc ((end - start + 1) * sizeof(char *));
	if (!cmd_lst->cmd_and_dep)
		exit (1);
	while (start < end)
	{
		cmd_lst->cmd_and_dep[i] =  ft_strdup(line_split[start]);
		i ++;
		start ++;
	}
	cmd_lst->cmd_and_dep[i] = 0;
}

static void	ft_fill_file(t_cmd_lst *cmd_list, char **line_split, t_token *line_token, int len)
{
	int	i;
	int	file_ct;
	int file_nbr;

	i = 0;
	file_nbr = ft_count_token(line_token, red, len) + ft_count_token(line_token, rednfile, len);
	file_ct = 0;
	cmd_list->file = malloc((file_nbr + 1) * sizeof(char*));
	while (i < len)
	{
		if (line_token[i] == file)
		{
			cmd_list->file[file_ct] = ft_strdup(line_split[i]);
			file_ct ++;
		}
		else if (line_token[i] == rednfile)
		{
			cmd_list->file[file_ct] = ft_substr(line_split[i],
			ft_go_to_chev_end(line_split[i]), ft_strlen(line_split[i]));
			file_ct ++;
		}
		i ++;
	}
	cmd_list->file[file_ct] = 0;
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