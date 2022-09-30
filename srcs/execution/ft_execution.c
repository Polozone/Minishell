
#include "../../includes/minishell.h"

extern int g_error;

int is_builtin_nofork(t_prg *data, t_cmd_lst *node)
{
	int exit_value;

	if (node->is_cmd_builtin == unset || node->is_cmd_builtin == cd || node->is_cmd_builtin == quit
		|| (node->is_cmd_builtin == export && node->cmd_and_dep[1] != NULL))
	{
		if (data->cmd_nbr != 1)
			return (0);
		if (node->is_cmd_builtin == export)
			_export_env(data, node);
		if (node->is_cmd_builtin == unset)
			_unset_env_parent(data, node);
		if (node->is_cmd_builtin == cd)
			_ch_dir(data);
		if (node->is_cmd_builtin == quit)
		{
			exit_value = _exit_builtins(node);
			if (exit_value == -1)
				return (0);
			else
				exit(exit_value);
		}
		return (0);
	}
	return (1);
}

int	is_builtin_fork(t_prg *data, t_cmd_lst *node)
{
	if (node->is_cmd_builtin == echo || node->is_cmd_builtin == pwd 
		|| node->is_cmd_builtin == env || node->is_cmd_builtin == export)
	{
		// dprintf(2, "OKOKOKOK\n");
		if ((strcmp(node->cmd_and_dep[0], "export") == 0) && node->cmd_and_dep[1] == NULL)
		{
			_print_env_declare(data);
			return (1);
		}
		if (node->is_cmd_builtin == echo)
		{
			_echo_exe(node, 1);
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
	data->pipe = malloc(sizeof(int) * ((data->cmd_nbr  - 1) * 2));
	if (data->pipe == NULL)
	{
		// FREE ALL AND EXIT
		// free_data();
		return (-1);
	}
	while (++i < data->cmd_nbr - 1)
		pipe(&data->pipe[i * 2]);
	return (0);
}

void _ft_forks(t_prg *data, t_cmd_lst *tmp)
{
	tmp = data->cmd_list;
	int	exit_status;

	while (tmp)
	{
		if (is_builtin_nofork(data, tmp))
		{
			data->pid[data->nbr_pid] = fork();
			if (data->pid[data->nbr_pid] == -1)
				g_error = 1;
			else if (data->pid[data->nbr_pid] == 0)
				_set_fd(tmp, data);
			if (tmp->heredoc_delimiter[0])
			{
				close(tmp->pipe_hd[0]);
				close(tmp->pipe_hd[1]);
			}
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
	return (0);
}

void	sig_parent_hd(void)
{
	write(2, "\n", 1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	sig_handler_parent_hd(int sig)
{
	// if (sig == SIGINT)
	// 	g_status = 1;
	sig_parent_hd();
}

void	sig_child(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	_init_heredoc(t_prg *data)
{
	t_cmd_lst	*tmp;
	int			i;

	tmp = data->cmd_list;
	int		pid;
	i = 0;
	while (tmp)
	{
		if (tmp->heredoc_delimiter[i])
		{
			while (tmp->heredoc_delimiter[i])
			{
				if (!tmp->heredoc_delimiter[i + 1])
					pipe(tmp->pipe_hd);
				signal(SIGINT, sig_handler_parent_hd);
				pid = fork();
				if (pid == -1)
				{
					// FREE AND EXIT;
				}
				else if (pid == 0)
				{
					sig_child();
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
	_init_heredoc(data);
	_ft_forks(data, NULL);
	return (0);
}
