/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:07:25 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/18 09:24:49 by mgolinva         ###   ########.fr       */
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
		ft_parse(&prg);
		// prg.cmd_list->cmd_and_dep = malloc(100);
		// if (g_error != 258)
		// {
		// for (int i = 0; prg.cells[i]; i ++)
		// 	printf("cells %d = %s\n", i, prg.cells[i]);
		// }
		/*for (int i = 0; prg.cmd_list[i]; i ++)
			for (int j = 0; prg.cmd_list[i][j]; j ++)
				printf("%s\n", prg.cmd_list[i][j]);*/
		// if (g_error != 258)
			// ft_free_parsing(&prg);
	}
}