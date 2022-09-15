/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollz_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:38:46 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/14 15:06:10 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_dollz_lst	*ft_last_dollz_list(t_dollz_lst *lst)
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

void	ft_add_back_dollz_list(t_dollz_lst **alpha, t_dollz_lst *newb)
{
	t_dollz_lst	*tmp;

	if (!alpha || !newb)
		return ;
	else if (!*alpha)
	{
		*alpha = newb;
		return ;
	}
	else
	{
		tmp = ft_last_dollz_list(*alpha);
		tmp->next = newb;
	}
}

t_dollz_lst	*ft_lstnew_dollz_list(char *word)
{
	t_dollz_lst	*cmd;

	cmd = malloc(sizeof(t_dollz_lst));
	if (!cmd)
		return (0);
	cmd->word = word;
	cmd->next = NULL;
	return (cmd);
}

void	ft_lstclear_dollz_list(t_dollz_lst **lst)
{
	t_dollz_lst	*elem;

	while (*lst != NULL)
	{
		elem = (*lst);
		free((*lst)->word);
		(*lst) = (*lst)->next;
		free(elem);
	}
	*lst = NULL;
}