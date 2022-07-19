/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:07:25 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/18 16:59:20 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error;

static void	ft_free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i ++;
	}
	free (array);
}

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

int main(int ac, char **av, char **env)
{
	t_prg prg;

	(void) ac;
	(void) av;
	prg.env_lst = ft_create_env_lst(env, &prg);

	setup_term();
	struct sigaction sa;
	sa.sa_handler = &handle_sigstp;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	while (1)
	{
		g_error = 0;
		prg.line = readline("Minichell_Drucker1.3$ ");
		add_history(prg.line);
		// printf("%s\n", rl_line_buffer);
		ft_parse(&prg);
		// if (g_error != 258)
		// {
		// for (int i = 0; prg.cells[i]; i ++)
		// 	printf("%s\n", prg.cells[i]);
		// for (int i = 0; prg.cmd_list[i]; i ++)
		// 	for (int j = 0; prg.cmd_list[i][j]; j ++)
		// 		printf("%s\n", prg.cmd_list[i][j]);
		
		// for (int i = 0; i < prg.cmd_nbr; i ++)
		// 	if (prg.is_cmd_builtin[i] == not_built_in)
		// 		printf ("nbr %d is not built in %d\n", i, prg.is_cmd_builtin[i]);
		// 	else
		// 		printf ("nbr %d is built in %d\n", i, prg.is_cmd_builtin[i]);
		// }
		// printf("g_error = %d\n", g_error);
		// // if (g_error != 258)
		// 	// ft_free_parsing(&prg);
	}
}