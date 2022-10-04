
#include "../../includes/minishell.h"

extern int	g_error;

int		_exit_builtins(t_cmd_lst *node)
{
	int					len;
	int					i;
	long long			exit_value;

	if (!node->cmd_and_dep[1])
	{
		write(1, "exit\n", 5);
		exit (0);
	}
	i = -1;
	len = ft_strlen_2d(node->cmd_and_dep);
	if (len > 2)
	{
		write(2, "exit\nexit: too many arguments\n", 30);
		g_error = 1;
		return (-1);
	}
	while (node->cmd_and_dep[1][++i])
	{
		if (node->cmd_and_dep[1][i] == '-' || node->cmd_and_dep[1][i] == '+')
			i++;
		if (!('0' <= node->cmd_and_dep[1][i] && node->cmd_and_dep[1][i] <= '9'))
		{
			ft_putstr_fd("exit\nexit: ", 2);
			ft_putstr_fd(node->cmd_and_dep[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (255);
		}
	}
	write(2, "exit\n", 5);
	exit_value = ft_atol(node->cmd_and_dep[1]);
	if (!checker_lli(node->cmd_and_dep[1]))
	{
		write(2, node->cmd_and_dep[1], ft_strlen(node->cmd_and_dep[1]));
		write(2, ": numeric argument required\n", 28);
	}
	return ((unsigned char)exit_value);
}