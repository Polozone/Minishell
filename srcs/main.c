/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:07:25 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/21 11:57:04 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error;

void	setup_term(void)
{
	struct termios	t;
	
	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	handle_sigstp(int sig)
{
	if (sig == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	_sig_handler(void)
{
	struct sigaction sa;
	
	setup_term();
	sa.sa_handler = &handle_sigstp;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

int	count_builtins_nofork(t_cmd_lst *list)
{
	t_cmd_lst	*tmp;
	int			nbr_builtins;

	tmp = list;
	nbr_builtins = 0;
	while (tmp)
	{
		if (tmp->is_cmd_builtin == export || tmp->is_cmd_builtin == unset || tmp->is_cmd_builtin == cd || tmp->is_cmd_builtin == quit)
		{
			//dprintf(2, "cmd = %s cmd flag == (%d)\n", tmp->cmd_and_dep[0], tmp->is_cmd_builtin);
			nbr_builtins++;
		}
		tmp = tmp->next;
	}
	// dprintf(2, "nbr buil == %d\n\n", nbr_builtins);
	return (nbr_builtins);
}

void _wait_pids(t_prg data)
{
	int	i;

	i = 0;
	while (i < data.cmd_nbr - data.nbr_builtins)
	{
		waitpid(data.pid[i], NULL, 0);
		i++;
	}
	// free(data.pid);
	return;
}

void env_to_tab(t_prg *prg, int i)
{
	t_env_lst	*tmp;
	int			size_lst;

	size_lst = _lst_size_env(prg->env_lst);
	prg->envp = malloc((sizeof(char *)) * size_lst + 1);
	tmp = prg->env_lst;
	while (tmp)
	{
		prg->envp[i] = ft_strjoin(ft_strjoin(tmp->name, "="), tmp->content);
		tmp = tmp->next;
		i++;
	}
	prg->envp[i] = 0;
}

void	_init_exe_var(t_prg *data)
{
	data->pid = NULL;
	// data->cmd_list->redir_fd = NULL;
	data->pipe = NULL;
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

int main(int ac, char **av, char **env)
{
	t_prg prg;

	(void)ac;
	(void)av;
	prg.env_lst = ft_create_env_lst(env, &prg);
	_init_exe_var(&prg);
	_sig_handler();
	while (1)
	{
		g_error = 0;
		prg.line = readline("Minichell_Drucker1.3$ ");
		if (prg.line == NULL)
			exit(0); // ctrl+d
		else if (ft_line_is_blank_space(prg.line) == false)
		{
			add_history(prg.line);
			env_to_tab(&prg, 0);
			ft_parse(&prg);
			if (g_error != 258)
			{
				_ft_exe(&prg);
				close_pipe(&prg);
				_wait_pids(prg);
				_ft_free_exe(&prg);
			}
		}
	}
}
