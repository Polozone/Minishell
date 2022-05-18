/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:27:13 by mgolinva          #+#    #+#             */
/*   Updated: 2022/03/08 10:21:36 by mgolinva         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_cmd	*ft_last(t_cmd *lst)
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

void	ft_add_back(t_cmd **alpha, t_cmd *newb)
{
	t_cmd	*tmp;

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

t_cmd	*ft_lstnew(char *content)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		return (0);
	}
	cmd->path = content;
	cmd->next = NULL;
	return (cmd);
}

void	ft_lstclear(t_cmd **lst)
{
	t_cmd	*elem;

	while (*lst != NULL)
	{
		elem = (*lst);
		free((*lst)->path);
		(*lst) = (*lst)->next;
		free(elem);
	}
	*lst = NULL;
}
