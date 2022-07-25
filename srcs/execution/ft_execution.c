
#include "../../includes/minishell.h"

void	is_builtin(t_prg data)
{
	if (data.cmd_list->is_cmd_builtin)
		if (data.cmd_list->is_cmd_builtin == echo)
			_echo_exe(&data, 0);
		if (data.cmd_list->is_cmd_builtin == cd)
			_ch_dir(&data);
		if (data.cmd_list->is_cmd_builtin == pwd)
			_pwd_exe();
		if (data.cmd_list->is_cmd_builtin == export)
			_export_env(&data);
		if (data.cmd_list->is_cmd_builtin == unset)
			_unset_env_parent(&data);
		if (data.cmd_list->is_cmd_builtin == env)
			_print_env(data.env_lst);
		if (data.cmd_list->is_cmd_builtin == quit)
			exit(0);
}

void	init_pipe(t_prg *data)
{
	int		i;

	i = -1;
	data->pipe = malloc(sizeof(int) * (data->cmd_nbr - 1) * 2);
	if (data->pipe == NULL)
	{
		// FREE ALL AND EXIT
		// free_data();
	}
	while (++i < data->cmd_nbr - 1)
		pipe(&data->pipe[i * 2]);
}

void	_ft_forks(t_prg *data)
{
	size_t	i;

	i = 0;
	while (i < data->cmd_nbr)
	{
		data->pid[i] = fork();
	}
	printf("%d", data->pid[i]);
}

void _ft_exe(t_prg *data)
{
	data->cmd_nbr = get_size_lst(data);
	data->pipe = malloc(sizeof(int) * data->cmd_nbr); // I WILL HAVE TO FREE PIPES FOR EACH CMD
	init_pipe(data);
	int i = 0;
	while (i < (data->cmd_nbr - 1) * 2)
	{
		printf("%d\n", data->pipe[i]);
		i++;
	}
	data->pid = malloc(sizeof(int) * data->cmd_nbr); // I WILL HAVE TO FREE PID ARRAY FOR EACH CMD
	_ft_forks(data);
	
	// tmp = data.cmd_list;
	// int i = 0;
	// int j = 0;
	// while (tmp)
	// {
	// 	i = 0;
	// 	while (tmp->cmd_and_dep[i])
	// 	{
	// 		j = 0;
	// 		while (tmp->file[j])
	// 		{
	// 			// printf("||||file = %s\n", tmp->file[j]);
	// 			j++;
	// 		}
	// 		j = 0;
	// 		while (j < tmp->redir_nbr)
	// 		{
	// 			printf("||||redir type == %d\n", tmp->redir_type[j]);
	// 			j++;
	// 		}
	// 		printf("%s\n", tmp->cmd_and_dep[i]);
	// 		i++;
	// 	}
	// 	tmp = tmp->next;
	// }
}