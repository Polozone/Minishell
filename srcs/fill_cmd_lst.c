/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:42:27 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/18 16:47:15 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_create_path_list(t_prg *prg)
{
	t_env_lst *buff;

	buff = prg->env_lst;
	while (buff != 0)
	{
		if (ft_strncmp(buff->name, "PATH=", 5) == 0)
		{
			prg->is_there_path = true;
			break;
		}
		buff = buff->next;
		prg->is_there_path = false;
	}
	if (prg->is_there_path == true)
		prg->path_list = ft_split(buff->content, ':');
}

void	ft_fill_cmd_and_dep(t_prg *prg, t_cmd_lst *cmd_lst, char **line_split, t_token *line_token)
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
	cmd_lst->cmd_and_dep = malloc ((end - start) * sizeof(char *));
	while (start < end)
	{
		cmd_lst->cmd_and_dep[i] =  ft_strdup(line_split[start]);
		i ++;
		start ++;
	}
	cmd_lst->cmd_and_dep[i] = 0;
}

void		ft_find_path(t_prg *prg, t_cmd_lst *cmd_list)
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
	ft_fill_cmd_and_dep(prg, cmd_lst, line_split, line_token);
	ft_find_path(prg, cmd_lst);
	ft_is_cmd_builtin(prg, cmd_lst);
	// ft_free_array(line_split);
	// ft_free_array(line_token);
}

void	ft_fill_cmd_lst(t_prg *prg)
{
	int	i;
	t_cmd_lst *buff;

	i = 0;
	buff = prg->cmd_list;
	ft_create_path_list(prg);
	while (prg->cells[i])
	{
		ft_fill_node(prg->cells[i], buff, prg);
		// printf("%s, built in = %d\n", prg->cmd_list->path, prg->cmd_list->is_cmd_builtin);
		i ++;
		buff = buff->next;
	}
	ft_redir_assignation(prg);
	// ft_free_array(prg->path_list);
}
