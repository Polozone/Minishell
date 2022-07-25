/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:34:01 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/25 17:38:38 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*static t_bool	ft_are_opening_and_closing(const char *line, int q_one, int q_two)
{
	int	i;
	int q_ct;

	i = q_one - 1;
	q_ct = 0;
	// printf("q_one = %d q_two + 1 = %d\n",q_one, q_two + 1);
	while (i >= 0)
	{
		if (line[i] == line[q_one])
			q_ct ++;
		i --;
	}
	// printf("q_ct before = %d\n", q_ct);
	if (q_ct % 2 != 0 && q_ct != 0)
	{
		printf("MERDEEEEEEE\n");
		return (false);
	}
	i = q_two + 1;
	q_ct = 0;
	while (line[i])
	{
		if (line[i] == line[q_two])
			q_ct ++;
		i ++;
	}
	// printf("q_ct after = %d\n", q_ct);
	if (q_ct % 2 != 0 && q_ct != 0)
	{
		printf("MERDEEEEEEE\n");
		return (false);
	}
	printf("BORDEL DE TCHOUCH\n");
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
	// printf("line[%d] = %s line = %s\n", index, &line[index], line);
	while (line[i])
	{
		// printf("q_one = %d, q_tzo = %d, index = %d\n", q_one, q_two, index);
		if ((q_one != -1 && q_two != -1 && index > q_one && index < q_two)
		&& (ft_are_opening_and_closing(line, q_one, q_two) == true))
		{
			return (true);

		}
		else if ( q_one != -1 && q_two != -1)
		{
			q_one = -1;
			q_two = -1;
		}
		else if (q_one != -1 && line[i] == 39)
		{
			q_one = i;
			printf("q_two = %d\n", q_two);
		}
		else if (line[i] == 39)
		{
			q_two = i;
			printf("q_one = %d\n", q_one);
		}
		i ++;
	}
	if ((q_one != -1 && q_two != -1 && index > q_one && index < q_two)
	&& (ft_are_opening_and_closing(line, q_one, q_two) == true))
	{

		return (true);
	}
	printf("TESTTTTTTTT\n");
	return (false);
}*/


// suggestion de Martin, on assigne un entier qui change de valeur en fonction de si on est entre quote ou pqs
// int	ft_quotes(char c, int q)
// {
// 	if (q == 0)
// 		if ('"')
// 			q = 2;
// 		if ('\'')
// 			q = 1;
// 	if (q == 1)
// 		if ('\'')
// 			q = 0;
// 	if (q == 2)
// 		if ('"')
// 			q = 0;
// }

t_bool	ft_is_in_single(const char *line, int index)
{
	int	i;
	int	q_ct_before;
	int	q_ct_after;

	i = 0;
	q_ct_before = 0;
	q_ct_after = 0;
	while (line[i] && i < index)
	{
		if (line[i] == 39 && ft_is_in_double(line, i) != true)
			q_ct_before ++;
		i ++;
	}
	while (line[i])
	{
		if (line[i] == 39 && ft_is_in_double(line, i) != true)
			q_ct_after ++;
		i ++;
	}
	if (q_ct_before % 2 != 0 && q_ct_after % 2 != 0)
		return (true);
	return (false);
}

t_bool	ft_is_in_double(const char *line, int index)
{
	int	i;
	int	q_ct_before;
	int	q_ct_after;

	i = 0;
	q_ct_before = 0;
	q_ct_after = 0;
	while (line[i] && i < index)
	{
		if (line[i] == 34 && ft_is_in_single(line, i) != true)
			q_ct_before ++;
		i ++;
	}
	while (line[i])
	{
		if (line[i] == 34 && ft_is_in_single(line, i) != true)
			q_ct_after ++;
		i ++;
	}
	if (q_ct_before % 2 != 0 && q_ct_after % 2 != 0)
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