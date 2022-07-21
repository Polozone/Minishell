/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:34:01 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/21 13:51:15 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_bool	ft_are_opening_and_closing(const char *line, int q_one, int q_two)
{
	int	i;
	int q_ct;

	i = q_one - 1;
	q_ct = 0;
	while (i >= 0)
	{
		if (line[i] == line[q_one])
			q_ct ++;
		i --;
	}
	if (q_ct % 2 == 0)
		return (false);
	i = q_two + 1;
	q_ct = 0;
	while (line[i])
	{
		if (line[i] == line[q_two])
			q_ct ++;
		i ++;
	}
	if (q_ct % 2 == 0)
	if (q_ct % 2 == 0)
		return (false);
	return (true);
}

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
		if ((q_one != -1 && q_two != -1 && index > q_one && index < q_two)
		&& (ft_are_opening_and_closing(line, q_one, q_two) == true))
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
	if ((q_one != -1 && q_two != -1 && index > q_one && index < q_two)
		&& (ft_are_opening_and_closing(line, q_one, q_two) == true))
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
		if ((q_one != -1 && q_two != -1 && index > q_one && index < q_two)
		&& (ft_are_opening_and_closing(line, q_one, q_two) == true))
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
	if ((q_one != -1 && q_two != -1 && index > q_one && index < q_two)
	&& (ft_are_opening_and_closing(line, q_one, q_two) == true))
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