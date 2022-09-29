
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
