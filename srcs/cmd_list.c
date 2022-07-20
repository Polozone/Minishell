/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:27:13 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/20 15:12:02 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_cmd_lst	*ft_last_cmd_list(t_cmd_lst *lst)
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

void	ft_add_back_cmd_list(t_cmd_lst **alpha, t_cmd_lst *newb)
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
		tmp = ft_last_cmd_list(*alpha);
		tmp->next = newb;
	}
}

t_cmd_lst	*ft_lstnew_cmd_list(void)
{
	t_cmd_lst	*cmd;

	cmd = malloc(sizeof(t_cmd_lst));
	if (!cmd)
		return (0);
	cmd->cmd_and_dep = 0;
	cmd->path = 0;
	cmd->file = 0;
	cmd->redir_type = 0;
	cmd->redir_nbr = 0;
	cmd->is_cmd_builtin = 0;
	cmd->heredoc_delimiter = 0;
	cmd->next = NULL;
	return (cmd);
}



void	ft_lstclear_cmd_list(t_cmd_lst **lst)
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
