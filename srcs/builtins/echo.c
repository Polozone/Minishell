
#include "../../includes/minishell.h"

int		check_args_echo(char	*str)
{
	int		i;

	i = 0;
	if (str[i] != '-')
		return (-1);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (-1);
	}
	return (0);
}

int		_echo_exe(t_prg *data, int i)
{
	int		flag;

	flag = 1;
	if (!data->cmd_list->cmd_and_dep[1])
	{
		printf("\n");
		return (0);
	}
	while (check_args_echo(data->cmd_list->cmd_and_dep[i]) == 0)
	{
		flag = 0;
		i++;
	}
	while (data->cmd_list->cmd_and_dep[i])
	{
		printf("%s", data->cmd_list->cmd_and_dep[i]);
		if (i != ft_strlen_2d(data->cmd_list->cmd_and_dep) - 1)
			printf(" ");
		i++;
	}
	if (flag)
		printf("\n");
	return (0);
}