/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:02:31 by mgolinva          #+#    #+#             */
/*   Updated: 2022/10/05 16:51:46 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static long	ft_checker(long result, long neg)
{
	if (result > 2147483648 || result < -2147483648)
	{
		if (neg == 1 > 0)
			return (-1);
		else
			return (0);
	}
	return (result * neg);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		i;
	int		result;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (8 < str[i] && str[i] < 14))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = sign * -1;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (ft_checker(result, sign));
}

long long int	ft_atol(const char *str)
{
	int					sign;
	int					i;
	long long int		result;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (8 < str[i] && str[i] < 14))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = sign * -1;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	charcmp(char a, char b)
{
	if (a > b)
		return (1);
	return (0);
}

int	checker_lli(char *to_cmp)
{
	int		i;
	char	*lli_max;
	char	*lli_min;

	i = -1;
	lli_max = "9223372036854775807";
	lli_min = "-9223372036854775808";
	if (ft_strlen(to_cmp) < 19)
		return (1);
	if (to_cmp[0] == '-')
	{
		i = 0;
		while (to_cmp[++i])
		{
			if (charcmp(to_cmp[i], lli_min[i]))
				return (0);
		}
	}
	else
		while (to_cmp[++i])
			if (charcmp(to_cmp[i], lli_max[i]))
				return (0);
	return (1);
}
