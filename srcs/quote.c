/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:34:01 by mgolinva          #+#    #+#             */
/*   Updated: 2022/05/20 14:44:11 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_bool	ft_is_in_double(const char *line, int index)
{
	int	q_one;
	int	q_two;
	int	i;

	i = 0;
	q_one = -1;
	q_two = -1;
	while (line[i])
	{
		if (q_one != -1 && q_two != -1 && index > q_one && index < q_two)
			return (true);
		else if ( q_one != -1 && q_two != -1)
		{
			q_one = -1;
			q_two = -1;
		}
		else if (q_one != -1 && line[i] == 34)
			q_two = i;
		else if (line[i] == 34)
			q_one = i;
		i ++;
	}
	if (q_one != -1 && q_two != -1 && index > q_one && index < q_two)
		return (true);
	return (false);
}

t_bool	ft_is_in_single(const char *line, int index)
{
	int	q_one;
	int	q_two;
	int	i;

	i = 0;
	q_one = -1;
	q_two = -1;
	while (line[i])
	{
		if (q_one != -1 && q_two != -1 && index > q_one && index < q_two)
			return (true);
		else if ( q_one != -1 && q_two != -1)
		{
			q_one = -1;
			q_two = -1;
		}
		else if (q_one != -1 && line[i] == 39)
			q_two = i;
		else if (line[i] == 39)
			q_one = i;
		i ++;
	}
	if (q_one != -1 && q_two != -1 && index > q_one && index < q_two)
		return (true);
	return (false);
}

t_bool	ft_is_in_quote(const char *line, int index)
{
	if (ft_is_in_double(line, index) == true)
		return (true);
	if (ft_is_in_single(line, index) == true)
		return (true);
	return (false);
}