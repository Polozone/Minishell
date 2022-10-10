/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:53:45 by mgolinva          #+#    #+#             */
/*   Updated: 2022/10/07 15:14:45 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_1d(void	**to_free)
{
	if (*to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
}

void	ft_free_2d(void	***to_free)
{
	if (**to_free)
	{
		free(**to_free);
		**to_free = NULL;
	}
}

void	ft_free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i ++;
	}
	free(array);
}
