/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_env_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:12:00 by mgolinva          #+#    #+#             */
/*   Updated: 2022/10/05 09:06:15 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_update_shell_lvl(t_prg *data, int update)
{
	t_env_lst	*tmp;
	char		*new_shell_lvl;
	int			shell_lvl;

	tmp = data->env_lst;
	while (tmp && tmp->name != NULL && ft_strcmp(tmp->name, "SHLVL") != 0)
		tmp = tmp->next;
	if (tmp != NULL)
	{
		shell_lvl = ft_atoi(tmp->content);
		shell_lvl += update;
		new_shell_lvl = ft_itoa(shell_lvl);
		free(tmp->content);
		tmp->content = new_shell_lvl;
	}
}
