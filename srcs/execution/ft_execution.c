/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:56:09 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/10 14:12:36 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

int	is_builtin_nofork(t_prg *data, t_cmd_lst *node)
{
	int	exit_value;

	if (node->is_cmd_builtin == unset || node->is_cmd_builtin == cd
		|| node->is_cmd_builtin == quit
		|| (node->is_cmd_builtin == export && node->cmd_and_dep[1] != NULL))
	{
		if (data->cmd_nbr != 1)
			return (0);
		if (node->is_cmd_builtin == export)
			_export_env(data, node);
		if (node->is_cmd_builtin == unset)
			_unset_env_parent(data, node);
		if (node->is_cmd_builtin == cd)
			_ch_dir(data, NULL);
		if (node->is_cmd_builtin == quit)
		{
			exit_value = _exit_builtins(node, -1, 0, 0);
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
		if ((strcmp(node->cmd_and_dep[0], "export") == 0)
			&& node->cmd_and_dep[1] == NULL)
			_print_env_declare(data);
		if (node->is_cmd_builtin == echo)
			_echo_exe(node, 1);
		if (node->is_cmd_builtin == pwd)
			_pwd_exe();
		if (node->is_cmd_builtin == env)
		{
			if (check_launch_env(node))
				_print_env(data->env_lst);
		}
		return (1);
	}
	return (0);
}

void	ft_sigignore(int sig)
{
	if (sig == 2)
	{
		write(2, "\n", 1);
		g_error = 130;
	}
	else if (sig == 3)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_error = 131;
	}
}

void	_ft_forks(t_prg *data, t_cmd_lst *tmp)
{
	tmp = data->cmd_list;
	signal(SIGINT, ft_sigignore);
	signal(SIGQUIT, ft_sigignore);
	while (tmp)
	{
		if (is_builtin_nofork(data, tmp) == 1)
		{
			data->pid[data->nbr_pid] = fork();
			if (data->pid[data->nbr_pid] == -1)
			{
				if (data->fork_capacity_met == false)
					ft_putstr_fd("minishell: fork: Resource "
						"temporarily unavailable\n", 2);
				data->fork_capacity_met = true;
			}
			else if (data->pid[data->nbr_pid] == 0)
			{
				g_error = _set_fd(tmp, data);
			}
			check_heredoc(tmp);
			data->nbr_pid++;
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
	_init_heredoc(data, -1, 0);
	if (data->has_heredoc_been_sig_ended == false)
		_ft_forks(data, NULL);
	else
		data->has_heredoc_been_sig_ended = false;
	return (0);
}
