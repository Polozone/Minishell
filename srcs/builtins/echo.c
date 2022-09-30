
#include "../../includes/minishell.h"

int		check_args_echo(char	*str)
{
	int		i;

	i = 0;
	if (str[0] != '-')
		return (0);
	if (str[0] == '-' && str[1] == '\0')
		return (0);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

int		_echo_exe(t_cmd_lst *node, int i)
{
	int		flag;

	flag = 1;
	if (!node->cmd_and_dep[1])
	{
		printf("\n");
		return (0);
	}
	while (check_args_echo(node->cmd_and_dep[i]))
	{
		flag = 0;
		i++;
	}
	while (node->cmd_and_dep[i])
	{
		printf("%s", node->cmd_and_dep[i]);
		if (i != ft_strlen_2d(node->cmd_and_dep) - 1)
			printf(" ");
		i++;
	}
	if (flag)
		printf("\n");
	return (0);
}