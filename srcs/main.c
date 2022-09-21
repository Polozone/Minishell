/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:07:25 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/20 10:32:21 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_error;

void ft_free_parsing(t_prg *prg)
{
	/*int	i;
	int	j;

	i = 0;
	free(prg->line);
	ft_free_char_array(prg->cells);
	while (prg->cmd_list[i])
	{
		j = 0;
		while (prg->cmd_list[i][j])
		{
			free(prg->cmd_list[i][j]);
			j ++;
		}
		free(prg->cmd_list[i]);
		i ++;
	}
	free(prg->cmd_list);*/
}

void setup_term(void)
{
	struct termios t;
	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void handle_sigstp(int sig)
{
	if (sig == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void _sig_handler()
{
	setup_term();
	struct sigaction sa;
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
		if (tmp->is_cmd_builtin == export || tmp->is_cmd_builtin == unset 
			|| tmp->is_cmd_builtin == cd || tmp->is_cmd_builtin == quit)
		{
			nbr_builtins++;
		}
		tmp = tmp->next;
	}
	return (nbr_builtins);
}

void _wait_pids(t_prg data)
{
	size_t	i;
	int		nbr_builtins;

	i = 0;
	while (i < data.cmd_nbr - data.nbr_builtins)
	{
		// dprintf(2, "Waiting...\n");
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
