/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:03:12 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/22 15:44:32 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_lstadd_front(t_gc_lst **alpha, t_gc_lst *newb)
{
	if (alpha != NULL && newb != NULL)
	{
		newb->next = *alpha;
		*alpha = newb;
	}
}

t_gc_lst	*ft_lstnew_gc_list(void *adress)
{
	t_gc_lst	*gc;

	gc = malloc(sizeof(t_gc_lst));
	if (env == NULL)
		exit (1);
	gc->adress = adress;
	gc->next = NULL;
	return (env);
}

void	ft_malloc(int size, void *adress, t_gc_lst *gc_lst)
{
	adress = malloc(size);
	if (!adress)
	{
		//free all
		exit (1);
	}
	if (gc_lst == NULL)
		ft_lstnew_gc_list(adress);
	else
		ft_lstadd_front(gc_lst, ft_lstnew_gc_list(adress));
}