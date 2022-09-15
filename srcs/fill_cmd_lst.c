/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:42:27 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/14 10:03:29 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_create_path_list(t_prg *prg)
{
	t_env_lst *buff;

	buff = prg->env_lst;
	while (buff != 0)
	{
		if (ft_strncmp(buff->name, "PATH", 5) == 0)
		{
			prg->is_there_path = true;
			break;
		}
		buff = buff->next;
		prg->is_there_path = false;
	}
	if (prg->is_there_path == true)
		prg->path_list = ft_split(buff->content, ':');
	// printf("buff name = %s path_list[0] =\n", buff->name);
}

t_bool	ft_is_there_dollzzz(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (true);
		i ++;
	}
	return (false);
}

void	ft_expend_env_variable(t_prg *prg, t_cmd_lst *cmd_lst)
{
	int	i;
	char *buff;

	i = 0;
	if (cmd_lst->cmd_and_dep == 0)
		return;
	while (cmd_lst->cmd_and_dep[i])
	{
		if (ft_is_there_dollzzz(cmd_lst->cmd_and_dep[i]) == true)
		{
			buff = cmd_lst->cmd_and_dep[i];
			cmd_lst->cmd_and_dep[i] =
			ft_forge_new_line(prg, cmd_lst->cmd_and_dep[i]);
			free(buff);
		}
		i ++;
	}
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
		ft_expend_env_variable(prg, buff);
		i ++;
		buff = buff->next;
	}
	t_cmd_lst *buff2 = prg->cmd_list;
	
	while (buff2)
	{
		if (buff2->cmd_and_dep != 0)
			for (int i = 0; buff2->cmd_and_dep[i]; i ++)
				printf("cmd_n_dep[%d] = %s\n", i, buff2->cmd_and_dep[i]);
		printf("path= %s\n", buff2->path);
		if (buff2->file != 0)
			for (int i = 0; buff2->file[i]; i ++)
				printf("file[%d] = %s\n", i, buff2->file[i]);
		if (buff2->redir_nbr != 0)			
			printf("redir_nbr = %d\n", buff2->redir_nbr);
		if (buff2->redir_type != 0)
			for (int i = 0; i < buff2->redir_nbr; i ++)
				printf("redir_type[%d] = %u\n", i, buff2->redir_type[i]);
		if (buff2->is_cmd_builtin != 0)
			printf("is_cmd_builtin = %d\n", buff2->is_cmd_builtin);
		buff2 = buff2->next;
	}
	// ft_free_array(prg->path_list);
}
