
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

int _init_pipe(t_prg *data)
{
	int i;

	i = -1;
	data->pipe = malloc(sizeof(int) * ((data->cmd_nbr  - 1 + data->heredoc_nbr) * 2));
	if (data->pipe == NULL)
	{
		// FREE ALL AND EXIT
		// free_data();
		return (-1);
	}
	// dprintf(2, "hd nbr == %d\n", data->heredoc_nbr);
	while (++i < data->cmd_nbr - 1 + data->heredoc_nbr)
	{
		// dprintf(2, "init pipe\n");
		pipe(&data->pipe[i * 2]);
	}
	return (0);
}

void _ft_forks(t_prg *data, t_cmd_lst *tmp)
{
	tmp = data->cmd_list;

	while (tmp)
	{
		if (is_builtin_nofork(data, tmp))
		{
			data->pid[data->nbr_pid] = fork();
			if (data->pid[data->nbr_pid] == -1)
			{
				// FREE ALL;
				// exit(0);
			}
			else if (data->pid[data->nbr_pid] == 0)
				_set_fd(tmp, data);
			data->nbr_pid++;
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

int	_alloc_exe_var(t_prg *data)
{
	data->pid = malloc(sizeof(int) * data->cmd_nbr); // I WILL HAVE TO FREE PID ARRAY FOR EACH CMD
	if (data->pid == NULL)
	{
		// free and return;
		return (-1);
	}
	data->cmd_list->redir_fd = malloc(sizeof(int) * data->cmd_list->redir_nbr);
	if (data->cmd_list->redir_fd == NULL)
	{
		// free and return ;
		return (-1);
	}
	return (0);
}

void	_init_heredoc(t_prg *data)
{
	t_cmd_lst	*tmp;
	int			i;
	// int			STDIN_TMP = dup(STDIN_FILENO);
	// int			STDOUT_TMP = dup(STDOUT_FILENO);

	i = 0;
	tmp = data->cmd_list;
	int		pid;
	while (tmp)
	{
		if (tmp->heredoc_delimiter[i])
		{
			while (tmp->heredoc_delimiter[i])
			{
				pid = fork();
				if (pid == -1)
				{
					// FREE AND EXIT;
				}
				else if (pid == 0)
				{
					_heredoc(data, tmp, i);
					exit (0);
				}
				waitpid(pid, NULL, 0);
				i++;
			}
			i = 0;
		}
		tmp = tmp->next;
	}
}

int	_ft_exe(t_prg *data)
{
	data->nbr_pid = 0;
	data->cmd_list->redir_fd = NULL;
	data->nbr_builtins = count_builtins_nofork(data->cmd_list);
	data->cmd_nbr = get_size_lst(data);
	_set_index_list(data);
	if (_init_pipe(data) || _alloc_exe_var(data))
		return (-1);
	// dprintf(2, "heredoc nbr == %d\n\n", data->heredoc_nbr);
	_init_heredoc(data);
	_ft_forks(data, NULL);
	return (0);
}
