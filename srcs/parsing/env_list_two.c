/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:55:57 by mgolinva          #+#    #+#             */
/*   Updated: 2022/10/05 11:08:04 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_lst	*ft_search_in_env_lst(t_prg *prg, char *name)
{
	t_env_lst	*buff;

	buff = prg->env_lst;
	while (buff != NULL)
	{
		if (ft_strcmp(buff->name, name) == 0)
			return (buff);
		buff = buff->next;
	}
	return (0);
}

t_env_lst	*ft_empty_env_lst(void)
{
	t_env_lst	*env;

	env = ft_lstnew_env_list(ft_strdup("PWD"), getcwd(NULL, 0));
	ft_add_back_env_list(&env,
		ft_lstnew_env_list(ft_strdup("SHLVL"), ft_strdup("0")));
	ft_add_back_env_list(&env,
		ft_lstnew_env_list(ft_strdup("_"), ft_strdup("/usr/bin/env")));
	return (env);
}
