/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_dealloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:03:31 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/28 09:26:09 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_int_array(int *array, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(&array[i]);
		i ++;
	}
	free(array);
}

void	ft_free_env_lst(t_prg *prg)
{
	t_env_lst	*tmp2;

	tmp2 = prg->env_lst;
	while (tmp2)
	{
		free(tmp2->content);
		free(tmp2->name);
		tmp2 = tmp2->next;
	}
	while (prg->env_lst)
	{
		tmp2 = prg->env_lst;
		prg->env_lst = prg->env_lst->next;
		free(tmp2);
	}
}

static void	ft_free_cmd_lst(t_prg *prg)
{
	t_cmd_lst	*tmp;

	tmp = prg->cmd_list;
	while (tmp)
	{
		if (tmp->cmd_and_dep != NULL)
			ft_free_char_array(tmp->cmd_and_dep);
		if (tmp->path)
			free(tmp->path);
		if (tmp->file != NULL)
			ft_free_char_array(tmp->file);
		if (tmp->redir_type != NULL)
			free(tmp->redir_type);
		if (tmp->heredoc_delimiter != NULL)
			ft_free_char_array(tmp->heredoc_delimiter);
		tmp = tmp->next;
	}
	while (prg->cmd_list)
	{
		tmp = prg->cmd_list;
		prg->cmd_list = prg->cmd_list->next;
		free(tmp);
	}
}

void	ft_free_parsing(t_prg *prg)
{
	if (prg->path_list != NULL)
		ft_free_char_array(prg->path_list);
	if (prg->envp != NULL)
		ft_free_char_array(prg->envp);
	if (prg->cells != NULL)
		ft_free_char_array(prg->cells);
	ft_free_cmd_lst(prg);
}
