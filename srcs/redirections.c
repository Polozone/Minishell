/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:00:01 by mgolinva          #+#    #+#             */
/*   Updated: 2022/06/14 11:03:49 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_count_redir(char *cells)
{
	int	j;
	int	redir_ct;
	int	cells_len = ft_strlen(cells); 

	j = 0;
	redir_ct = 0;
	while (cells[j])
	{
		if (j < cells_len - 1 && cells[j] == '>' &&cells[j + 1] == '>')
		{
			j ++;
			redir_ct ++;
		}
		else if (j < cells_len - 1 && cells[j] == '>'&& cells[j + 1] != '>')
			redir_ct ++;
		else if (j < cells_len - 1 && cells[j] == '<'&& cells[j + 1] == '<')
		{
			j ++;
			redir_ct ++;
		}
		else if (j < cells_len - 1 && cells[j] == '<' && cells[j + 1] != '<')
			redir_ct ++;
		j ++;
	}
	return (redir_ct);
}

void	ft_redir_assignation(t_prg *prg)
{
	int	i;
	int	j;
	int	redir_ct; 
	t_cmd_lst *buff;

	i = 0;
	buff = prg->cmd_list;
	while (prg->cells[i] && buff)
	{
		j = 0;
		redir_ct = 0;
		buff->redir_nbr = ft_count_redir(prg->cells[i]);
		buff->redir_type = malloc(buff->redir_nbr * sizeof(t_redir));
		if (buff->redir_type == 0)
			exit (0);
		while (prg->cells[i][j] && buff)
		{
			if ((j < ft_strlen(prg->cells[i]) - 1 && prg->cells[i][j] == '>')
			&& (prg->cells[i][j + 1] == '>'))
			{
				buff->redir_type[redir_ct] = out_append;
				redir_ct ++;
				j ++;
			}
			else if ((j < ft_strlen(prg->cells[i]) - 1 && prg->cells[i][j] == '>')
			&& (prg->cells[i][j + 1] != '>'))
			{
				buff->redir_type[redir_ct] = output;
				redir_ct ++;
			}
			else if ((j < ft_strlen(prg->cells[i]) - 1 && prg->cells[i][j] == '<')
			&& (prg->cells[i][j + 1] == '<'))
			{
				buff->redir_type[redir_ct] = heredoc;
				redir_ct ++;
				j ++;
			}
			else if ((j < ft_strlen(prg->cells[i]) - 1 && prg->cells[i][j] == '<')
			&& (prg->cells[i][j + 1] != '<'))
			{
				buff->redir_type[redir_ct] = input;
				redir_ct ++;
			}
			j ++;
		}
		buff = buff->next;
		i ++;
	}
}