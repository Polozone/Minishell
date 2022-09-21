/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:28:29 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/21 13:49:37 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

void	ft_error_print(t_cmd_lst *node, int error_code, char *error_source)
{
	if (error_code == 127 && node->heredoc_delimiter[0]
		== NULL && node->cmd_and_dep[0] != NULL && node->is_cmd_builtin == not_built_in)
	{
		printf("Minichell: %s: command not found\n", error_source);
		g_error = 127;
	}
}