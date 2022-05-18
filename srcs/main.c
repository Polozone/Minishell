/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:07:25 by mgolinva          #+#    #+#             */
/*   Updated: 2022/05/18 10:17:04 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	int	i;
	int	j;

	i = 0;
	free(prg->line);
	if (prg->path != NULL)
		ft_free_char_array(prg->path);
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
	free(prg->cmd_list);
}

int main(int ac, char **av, char **env)
{
	t_prg prg;

	(void) ac;
	(void) av;
	g_error = 0;
	while (1)
	{
		prg.env_p = env;
		prg.line = readline("Minichell_Drucker1.3$ ");
		ft_parse(&prg);
		/*for (int i = 0; prg.cells[i]; i ++)
			printf("%s\n", prg.cells[i]);*/
		for (int i = 0; prg.cmd_list[i]; i ++)
			for (int j = 0; prg.cmd_list[i][j]; j ++)
				printf("%s\n", prg.cmd_list[i][j]);
		
		/*for (int i = 0; i < prg.cmd_nbr; i ++)
			if (prg.is_cmd_builtin[i] == not_built_in)
				printf ("nbr %d is not built in %d\n", i, prg.is_cmd_builtin[i]);
			else
				printf ("nbr %d is built in %d\n", i, prg.is_cmd_builtin[i]);*/
		ft_free_parsing(&prg);
	}
}