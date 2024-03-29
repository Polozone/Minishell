/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:03:57 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/05 14:15:57 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	_ft_free_exe(t_prg *data)
{
	ft_free_1d((void **)&data->pid);
	ft_free_1d((void **)&data->pipe);
	ft_free_1d((void **)&data->cmd_list->redir_fd);
}

void	_ft_free_and_exit(t_prg *data)
{
	ft_free_parsing(data);
	_ft_free_exe(data);
	exit (0);
}
