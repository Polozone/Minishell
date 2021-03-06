/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:27:13 by mgolinva          #+#    #+#             */
/*   Updated: 2022/05/18 14:20:36 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_cmd_lst	*ft_last(t_cmd_lst *lst)
{
	void	*p;

	if (lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		p = lst;
		lst = lst->next;
	}
	return (p);
}

void	ft_add_back(t_cmd_lst **alpha, t_cmd_lst *newb)
{
	t_cmd_lst	*tmp;

	if (!alpha || !newb)
		return ;
	else if (!*alpha)
	{
		*alpha = newb;
		return ;
	}
	else
	{
		tmp = ft_last(*alpha);
		tmp->next = newb;
	}
}

void	ft_lstclear(t_cmd_lst **lst)
{
	t_cmd_lst	*elem;

	while (*lst != NULL)
	{
		elem = (*lst);
		free((*lst)->path);
		(*lst) = (*lst)->next;
		free(elem);
	}
	*lst = NULL;
}
