
#include "../../includes/minishell.h"

int is_builtin_nofork(t_prg *data, t_cmd_lst *node)
{
	if (node->is_cmd_builtin == export || node->is_cmd_builtin == unset 
		|| node->is_cmd_builtin == cd || node->is_cmd_builtin == quit)
	{
		if (data->cmd_nbr != 1)
			return (0);
		if (node->is_cmd_builtin == export)
		{
			_export_env(data);
			return (0);
		}
		if (node->is_cmd_builtin == unset)
		{
			_unset_env_parent(data, node);
			return (0);
		}
		if (node->is_cmd_builtin == cd)
		{
			_ch_dir(data);
			return (0);
		}
		if (node->is_cmd_builtin == quit)
			exit(0);
	}
	return (1);
}

int	is_builtin_fork(t_prg *data, t_cmd_lst *node)
{
	if (node->is_cmd_builtin == echo || node->is_cmd_builtin == pwd 
		|| node->is_cmd_builtin == env)
	{
		if (node->is_cmd_builtin == echo)
		{
			_echo_exe(data, 0);
			return (1);
		}
		if (node->is_cmd_builtin == pwd)
		{
			_pwd_exe();
			return (1);
		}
		if (node->is_cmd_builtin == env)
		{
			_print_env(data->env_lst);
			return (1);
		}
	}
	return (0);
}

void init_pipe(t_prg *data)
{
	int i;

	i = -1;
	data->pipe = malloc(sizeof(int) * ((data->cmd_nbr - 1) * 2));
	if (data->pipe == NULL)
	{
		// FREE ALL AND EXIT
		// free_data();
	}
	while (++i < data->cmd_nbr - 1)
		pipe(&data->pipe[i * 2]);
}

void _ft_forks(t_prg *data)
{
	int j;
	t_cmd_lst *tmp;

	tmp = data->cmd_list;
	j = 0;
	while (tmp)
	{
		if (is_builtin_nofork(data, tmp))
		{
			data->pid[j] = fork();
			if (data->pid[j] == -1)
			{
				// FREE ALL;
				// exit(0);
			}
			if (data->pid[j] == 0)
				_set_fd(tmp, data);
			j++;
		}
		tmp = tmp->next;
	}
}

void _set_index_list(t_prg *data)
{
	t_cmd_lst *tmp;
	int i;

	i = 0;
	tmp = data->cmd_list;
	while (tmp)
	{
		tmp->index = i;
		i++;
		tmp = tmp->next;
	}
}

void _ft_exe(t_prg *data)
{
	data->nbr_builtins = count_builtins_nofork(data->cmd_list);
	data->cmd_nbr = get_size_lst(data);
	_set_index_list(data);
	init_pipe(data);
	data->pid = malloc(sizeof(int) * data->cmd_nbr); // I WILL HAVE TO FREE PID ARRAY FOR EACH CMD
	data->cmd_list->redir_fd = malloc(sizeof(int) * data->cmd_list->redir_nbr);
	_ft_forks(data);
}
