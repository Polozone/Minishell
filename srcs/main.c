/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:07:25 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/25 16:52:47 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error;

void	ft_free_parsing(t_prg *prg)
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

void setup_term(void) {
    struct termios t;
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

void	_sig_handler()
{
	setup_term();
	struct sigaction sa;
	sa.sa_handler = &handle_sigstp;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

void	_wait_pids(t_prg data)
{
	size_t	i;

	i = 0;
	while (i < data.cmd_nbr)
	{
		waitpid(data.pid[i], NULL, 0);
		i++;
	}
}

int main(int ac, char **av, char **env)
{
	t_prg prg;

	(void) ac;
	(void) av;
	prg.env_lst = ft_create_env_lst(env, &prg);
	_sig_handler();
	while (1)
	{
		g_error = 0;
		prg.line = readline("Minichell_Drucker1.3$ ");
		if (prg.line == NULL)
			exit (0);
		add_history(prg.line);
		ft_parse(&prg);
		// _ft_exe(&prg);
		// _ft_free_exe(&prg);
		// _wait_pids(prg);
		// ft_free_parsing(&prg);
	}
}