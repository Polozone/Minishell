/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_env_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:12:00 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/30 16:00:42 by mgolinva         ###   ########.fr       */
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
	shell_lvl = atoi(tmp->content); //mettre ft_atoi
	shell_lvl += update;
	new_shell_lvl = ft_itoa(shell_lvl);
	free(tmp->content);
	tmp->content = new_shell_lvl;
	}
}
