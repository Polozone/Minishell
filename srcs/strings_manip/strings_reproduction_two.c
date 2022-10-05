/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_reproduction_two.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:33:22 by mgolinva          #+#    #+#             */
/*   Updated: 2022/10/05 12:59:36 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_dup_cmd(char **cmd, char **split_line, int j)
{
	*cmd = ft_strdup(*split_line);
	j ++;
	return (j);
}

char	*ft_join_shrtct(char *str1, char *str2)
{
	char	*new_line;

	new_line = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (new_line);
}
