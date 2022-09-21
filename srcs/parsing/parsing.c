/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:42:34 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/21 09:46:09 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_error;

static t_cmd_lst	*ft_create_cmd_lst(t_prg *prg)
{
	int	i;

	prg->cmd_list = ft_lstnew_cmd_list();
	i = 1;
	while (i < prg->cmd_nbr)
	{
		ft_add_back_cmd_list(&prg->cmd_list, ft_lstnew_cmd_list());
		i ++;
	}
	return (prg->cmd_list);
}

void	ft_parse(t_prg *prg)
{
	int i = 0;
	prg->cells = 0;
	if (prg->line == NULL)
		return;
	prg->line_len = ft_strlen(prg->line);
	if (ft_syntax_error(prg) == true)
	{
		g_error = 258;
		return;		
	}
	prg->cells = ft_split(prg->line, '|');
	prg->cmd_nbr = ft_array_len(prg->cells);
	prg->cmd_list = ft_create_cmd_lst(prg);
	ft_fill_cmd_lst(prg);
	t_cmd_lst *buff2 = prg->cmd_list;
	
	while (buff2)
	{
		printf ("IN PARSE\n");
		if (buff2->cmd_and_dep != 0)
			for (int i = 0; buff2->cmd_and_dep[i]; i ++)
				printf("cmd_n_dep[%d] = %s\n", i, buff2->cmd_and_dep[i]);
		printf("path= %s\n", buff2->path);
		if (buff2->file != 0)
			for (int i = 0; buff2->file[i]; i ++)
				printf("file[%d] = %s\n", i, buff2->file[i]);
		if (buff2->redir_nbr != 0)			
			printf("redir_nbr = %d\n", buff2->redir_nbr);
		if (buff2->redir_type != 0)
			for (int i = 0; i < buff2->redir_nbr; i ++)
				printf("redir_type[%d] = %u\n", i, buff2->redir_type[i]);
		if (buff2->heredoc_delimiter != 0)
			for(int i = 0; buff2->heredoc_delimiter[i]; i ++)
			{
				printf("I = %d\n", i);
				printf("heredoc delimiter[%d] = %s\n", i, buff2->heredoc_delimiter[i]);
			}
		if (buff2->is_cmd_builtin != 0)
			printf("is_cmd_builtin = %d\n", buff2->is_cmd_builtin);
		buff2 = buff2->next;
	}
	// ft_builtin_args(prg);
}