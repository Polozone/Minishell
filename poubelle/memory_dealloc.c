/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_dealloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:03:31 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/20 09:42:29 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_int_array(int *array, int len)
{
	int	i;

	i = 0;
	while(i < len)
	{
		free(array[i]);
		i ++;
	}
	free(array);
}

void	ft_free_cmd_list(t_prg *prg)
{
	t_cmd_lst *tmp;

	tmp = prg->cmd_list;
	if (prg->path_list != NULL);
		ft_free_char_array(prg->path_list);
	if (prg->envp != NULL)
		ft_free_char_array(prg->envp);
	if (prg->cells != NULL)
		ft_free_char_array(prg->cells);
	if (prg->line != NULL)
		free(prg->line);
	while (tmp)
	{
		if (tmp->cmd_and_dep != NULL)
			ft_free_char_array(tmp->cmd_and_dep);
		if (tmp->path)
			free(tmp->path);
		if (tmp->file != NULL)
			ft_free_char_array(tmp->file);
		if (tmp->redir_nbr)
			ft_free_int_array((int *)tmp->redir_type, tmp->redir_nbr);
		if (tmp->heredoc_delimiter != NULL)
			ft_free_char_array(tmp->heredoc_delimiter)
		if (tmp->redir)
		tmp = tmp->next;
	}
}