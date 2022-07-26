/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:07:25 by mgolinva          #+#    #+#             */
/*   Updated: 2022/06/16 11:22:56 by mgolinva         ###   ########.fr       */
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


int main(int ac, char **av, char **env)
{
	t_prg prg;
	// int : kirby;

	(void) ac;
	(void) av;
	prg.env_lst = ft_create_env_lst(env, &prg);
	while (1)
	{
		g_error = 0;
		prg.line = readline("Minichell_Drucker1.3$ ");
		// printf("%s\n\n\n", prg.cmd_list->cmd_and_dep[0]);
		// printf("line = %s\n", prg.line);
		ft_parse(&prg);
		prg.cmd_list->cmd_and_dep = malloc(1000);
		prg.cmd_list->cmd_and_dep[0] = malloc(1000);
		prg.cmd_list->cmd_and_dep[1] = malloc(1000);
		prg.cmd_list->cmd_and_dep[2] = malloc(1000);
		prg.cmd_list->cmd_and_dep[3] = malloc(1000);
		prg.cmd_list->cmd_and_dep[4] = malloc(1000);
		prg.cmd_list->cmd_and_dep[5] = malloc(1000);
		prg.cmd_list->cmd_and_dep[0] = "echo";
		prg.cmd_list->cmd_and_dep[1] = "blabliblouu";
		prg.cmd_list->cmd_and_dep[2] = "mega";
		prg.cmd_list->cmd_and_dep[3] = "echooo";
		prg.cmd_list->cmd_and_dep[4] = "yessss";
		prg.cmd_list->cmd_and_dep[5] = 0x0;
		_echo_exe(&prg);
		/*if (g_error != 258)
		{
		for (int i = 0; prg.cells[i]; i ++)
			printf("%s\n", prg.cells[i]);
		for (int i = 0; prg.cmd_list[i]; i ++)
			for (int j = 0; prg.cmd_list[i][j]; j ++)
				printf("%s\n", prg.cmd_list[i][j]);
		
		for (int i = 0; i < prg.cmd_nbr; i ++)
			if (prg.is_cmd_builtin[i] == not_built_in)
				printf ("nbr %d is not built in %d\n", i, prg.is_cmd_builtin[i]);
			else
				printf ("nbr %d is built in %d\n", i, prg.is_cmd_builtin[i]);
		}
		// printf("g_error = %d\n", g_error);
		// if (g_error != 258)
		ft_free_parsing(&prg);*/
	}
}