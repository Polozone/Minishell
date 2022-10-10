/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:17:26 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/10 14:01:09 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

void	sig_parent_hd(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	sig_handler_parent_hd(int sig)
{
	if (sig == SIGINT)
		g_error = 1;
	sig_parent_hd();
}

t_bool	ft_waitpid_hd(t_prg *data, int pid)
{
	int	ptr;

	waitpid(pid, &ptr, 0);
	if (WIFEXITED(ptr) == 1)
	{
		g_error = WEXITSTATUS(ptr);
		return (false);
	}
	if (WIFSIGNALED(ptr) == 1)
	{
		if (WTERMSIG(ptr) == 2)
		{
			data->has_heredoc_been_sig_ended = true;
			return (true);
		}
	}
	return (false);
}

void	_init_heredoc(t_prg *data, int i, int pid)
{
	t_cmd_lst	*tmp;

	tmp = data->cmd_list;
	while (tmp)
	{
		while (tmp->heredoc_delimiter[++i])
		{
			if (!tmp->heredoc_delimiter[i + 1])
				pipe(tmp->pipe_hd);
			signal(SIGINT, sig_handler_parent_hd);
			pid = fork();
			if (pid == -1)
				_ft_free_and_exit(data);
			else if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				_heredoc(data, tmp, i);
				exit (0);
			}
			if (ft_waitpid_hd(data, pid) == true)
				return ;
		}
		i = -1;
		tmp = tmp->next;
	}
}

void	_heredoc(t_prg *data, t_cmd_lst *tmp, int i)
{
	char	*line;
	char	*buf;
	int		longest;

	line = NULL;
	while (1)
	{
		longest = ft_strlen(tmp->heredoc_delimiter[i]);
		buf = readline("> ");
		if (buf == NULL)
			exit(0);
		if (ft_strlen(buf) > longest)
			longest = ft_strlen(buf);
		if (ft_strncmp(buf, tmp->heredoc_delimiter[i], longest) == 0)
		{
			free(buf);
			break ;
		}
		buf = ft_strjoin_hd(buf, "\n");
		line = ft_strjoin_hd(line, buf);
		free(buf);
	}
	buf = line;
	line = ft_forge_new_line_heredoc(data, line);
	_close_pipe_hd(tmp, line, buf, i);
}
