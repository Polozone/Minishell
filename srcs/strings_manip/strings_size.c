/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:28:51 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/21 17:33:29 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_array_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i ++;
	return (i);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i ++;
	return (i);
}

int ft_strlen_2d(char **str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

int		ft_strlen_to_char(char *str, char c)
{
	int i	= 0;

	while (str[i] != c && str[i])
		i++;
	return (i);
}