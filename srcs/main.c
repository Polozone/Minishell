/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:07:25 by mgolinva          #+#    #+#             */
/*   Updated: 2022/10/04 14:13:07 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error;

int	count_builtins_nofork(t_cmd_lst *list)
{
	t_cmd_lst	*tmp;
	int			nbr_builtins;

	tmp = list;
	nbr_builtins = 0;
	while (tmp)
	{
		if ((tmp->is_cmd_builtin == export && tmp->cmd_and_dep[0] == NULL)
			|| tmp->is_cmd_builtin == unset
			|| tmp->is_cmd_builtin == cd
			|| tmp->is_cmd_builtin == quit)
		{
			nbr_builtins++;
		}
		tmp = tmp->next;
	}
	return (nbr_builtins);
}

void	_wait_pids(t_prg *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_nbr - data->nbr_builtins)
	{
		waitpid(data->pid[i], &g_error, 0);
		if (data->fork_capacity_met == true)
		{
			g_error = 1;
		}
		else if (WIFEXITED(g_error) == 1)
			g_error = WEXITSTATUS(g_error);
		else if (WIFSIGNALED(g_error) == 1)
		{
			g_error = WEXITSTATUS(g_error);
			write(2, "\n", 1);
		}
		i++;
	}
	data->fork_capacity_met = false;
	return ;
}

void	env_to_tab(t_prg *prg, int i)
{
	t_env_lst	*tmp;
	int			size_lst;
	char		*tmp_name;

	size_lst = _lst_size_env(prg->env_lst);
	prg->envp = malloc((sizeof(char *)) * size_lst + 1);
	tmp = prg->env_lst;
	while (tmp)
	{
		tmp_name = ft_strjoin(tmp->name, "=");
		prg->envp[i] = ft_strjoin(tmp_name, tmp->content);
		tmp = tmp->next;
		free(tmp_name);
		i++;
	}
	prg->envp[i] = 0;
}

void	_init_exe_var(t_prg *data)
{
	data->pid = NULL;
	data->pipe = NULL;
	data->fork_capacity_met = false;
}

static t_bool	ft_line_is_blank_space(char *line)
{
	int	i;

	i = 0;
	if (line[i] == 0)
		return (true);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '	')
			return (false);
		i ++;
	}
	return (true);
}

int	main(int ac, char **av, char **env)
{
	t_prg	prg;

	(void)ac;
	(void)av;
	prg.env_lst = ft_create_env_lst(env, &prg);
	ft_update_shell_lvl(&prg, 1);
	_init_exe_var(&prg);
	tcgetattr(0, &prg.old_termios);
	prg.new_termios = prg.old_termios;
	prg.new_termios.c_lflag &= ~ECHOCTL;
	while (1)
	{
		// sig_parent();
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, _sig_stp_main);
		tcsetattr(0, TCSANOW, &prg.new_termios);
		prg.line = readline("Minichell_Drucker1.3$ ");
		if (prg.line == NULL)
		{
			ft_putstr_fd("exit\n", 2);
			exit(g_error); // ctrl+d
		}
		else if (ft_line_is_blank_space(prg.line) == false)
		{
			add_history(prg.line);
			if (ft_syntax_error(&prg) == true)
				g_error = 258;
			else
			{
				env_to_tab(&prg, 0);
				ft_parse(&prg);
				tcsetattr(0, TCSANOW, &prg.new_termios);
				_ft_exe(&prg);
				tcsetattr(0, TCSANOW, &prg.old_termios);
				close_pipe(&prg);
				_wait_pids(&prg);
				_ft_free_exe(&prg);
				ft_free_parsing(&prg);
			}
		}
		free(prg.line);
	}
	ft_free_env_lst(&prg);
}
