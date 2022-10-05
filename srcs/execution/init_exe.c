/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:21:57 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/05 14:22:52 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

int	_init_pipe(t_prg *data)
{
	int	i;

	i = -1;
	data->pipe = malloc(sizeof(int) * ((data->cmd_nbr - 1) * 2));
	if (data->pipe == NULL)
		_ft_free_and_exit(data);
	while (++i < data->cmd_nbr - 1)
		pipe(&data->pipe[i * 2]);
	return (0);
}

int	_alloc_exe_var(t_prg *data)
{
	data->pid = malloc(sizeof(int) * data->cmd_nbr);
	if (data->pid == NULL)
		_ft_free_and_exit(data);
	return (0);
}

void	_set_index_list(t_prg *data)
{
	t_cmd_lst	*tmp;
	int			i;

	i = 0;
	tmp = data->cmd_list;
	while (tmp)
	{
		tmp->index = i;
		i++;
		tmp = tmp->next;
	}
}
