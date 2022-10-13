/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _execute_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:37:56 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/13 14:09:02 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

int	is_file(const char *path)
{
	struct stat		path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

void	close_pipe(t_prg *data)
{
	int		i;

	i = 0;
	while (i < ((data->cmd_nbr - 1) * 2))
	{
		close(data->pipe[i]);
		i++;
	}
}

void	_init_fd(t_prg *data)
{
	t_cmd_lst	*tmp;

	tmp = data->cmd_list;
	while (tmp)
	{
		tmp->infile = 0;
		tmp->outfile = 1;
		tmp = tmp->next;
	}
}

int	_ft_execve(t_prg *data, t_cmd_lst *tmp)
{
	if (execve(tmp->path, tmp->cmd_and_dep, data->envp) == -1)
	{
		if (tmp->cmd_and_dep[0] && ft_strncmp(tmp->cmd_and_dep[0], "./", 2) == 0
			&& is_file(tmp->cmd_and_dep[0]) == 1)
			exit (ft_error_print_two(tmp, -126, tmp->cmd_and_dep[0]));
		else if ((access(tmp->cmd_and_dep[0], X_OK) != 0)
			&& (access(tmp->cmd_and_dep[0], F_OK) == 0)
			&& (ft_strncmp(tmp->cmd_and_dep[0], "./", 2) == 0))
			exit (ft_error_print_two(tmp, 126, tmp->cmd_and_dep[0]));
		else if (tmp->cmd_and_dep[0] != 0
			&& ft_strcmp(tmp->cmd_and_dep[0], ".") == 0)
			exit (ft_error_print_one(tmp, 2, tmp->cmd_and_dep[0]));
		else if (((tmp->path == NULL || access(tmp->path, F_OK) != 0)
				&& (ft_strstr(tmp->cmd_and_dep[0], "/") == 0))
			|| (tmp->cmd_and_dep[0] != 0
				&& ft_strcmp(tmp->cmd_and_dep[0], "..") == 0))
			exit (ft_error_print_one(tmp, 127, tmp->cmd_and_dep[0]));
		else if ((tmp->cmd_and_dep[0])
			&& (ft_strstr(tmp->cmd_and_dep[0], "/") != 0))
			exit (ft_error_print_three(tmp, 127, tmp->cmd_and_dep[0]));
	}
	exit (ft_error_print_one(tmp, 127, tmp->cmd_and_dep[0]));
}

int	_set_fd(t_cmd_lst *tmp, t_prg *data)
{
	tmp->redir_fd = malloc(sizeof(int) * tmp->redir_nbr);
	if (tmp->redir_fd == NULL)
		_ft_free_and_exit(data);
	_init_fd(data);
	_set_pipes(data, tmp);
	if (tmp->heredoc_delimiter[0])
	{
		dup2(tmp->pipe_hd[0], 0);
		close(tmp->pipe_hd[0]);
		close(tmp->pipe_hd[1]);
	}
	close_pipe(data);
	if (is_builtin_fork(data, tmp))
		exit (0);
	exit (_ft_execve(data, tmp));
}
