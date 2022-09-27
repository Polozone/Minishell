/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:55:57 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/22 10:58:21 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_lst	*ft_search_in_env_lst(t_prg *prg, char *name)
{
	t_env_lst	*buff;

	buff = prg->env_lst;
	while (buff != NULL)
	{
		if (ft_strstr(buff->name, name) != 0)
			return (buff);
		buff = buff->next;
	}
	return (0);
}
