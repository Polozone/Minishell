/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:42:27 by mgolinva          #+#    #+#             */
/*   Updated: 2022/06/14 15:09:06 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*ft_get_cmd_and_dep(t_prg *prg)
{
	t_cmd_lst *buff;

	buff = prg->cmd_list;

}*/

void	ft_fill_cmd_lst(t_prg *prg)
{
	ft_is_cmd_builtin(prg);
	//ft_get_cmd_and_dep(prg);
	ft_redir_assignation(prg);
}
