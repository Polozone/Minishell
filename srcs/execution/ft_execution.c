
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
	t_cmd_lst *tmp;

	tmp = data->cmd_list;
	while (i < data->cmd_nbr)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
		{
			// FREE ALL;
			exit (0);
		}
		if (data->pid[i] == 0)
			_execute_cmds(data, i, tmp);
		tmp = tmp->next;
		i++;
	}
}

void	_set_index_list(t_prg *data)
{
	t_cmd_lst	*tmp;
	int			i;

	tmp = data->cmd_list;
	i = 0;
	while (tmp)
	{
		tmp->index = i;
		i++;
		tmp = tmp->next;
	}
}

void _ft_exe(t_prg *data)
{
	data->cmd_nbr = get_size_lst(data);
	_set_index_list(data);
	init_pipe(data);
	data->pid = malloc(sizeof(int) * data->cmd_nbr); // I WILL HAVE TO FREE PID ARRAY FOR EACH CMD
	_ft_forks(data);
}