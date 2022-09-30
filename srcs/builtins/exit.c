
#include "../../includes/minishell.h"

int		_exit_builtins(t_cmd_lst *node)
{
	int		len;
	int		i;
	int		exit_value;

	if (!node->cmd_and_dep[1])
	{
		write(1, "exit\n", 5);
		exit (0);
	}
	i = -1;
	len = ft_strlen_2d(node->cmd_and_dep);
	if (len > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		return (1);
	}
	while (node->cmd_and_dep[1][++i])
	{
		if (node->cmd_and_dep[1][i] == '-')
			i++;
		if (!('0' <= node->cmd_and_dep[1][i] && node->cmd_and_dep[1][i] <= '9'))
		{
			dprintf(2, "exit: %s: numeric argument required\n", node->cmd_and_dep[1]);	
			return (255);
		}
	}
	exit_value = ft_atoi(node->cmd_and_dep[1]);
	return ((unsigned char)exit_value);
}