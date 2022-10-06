/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_reproduction_two.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:33:22 by mgolinva          #+#    #+#             */
/*   Updated: 2022/10/06 09:03:28 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_get_dep(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '>' || word[i] == '<')
			break ;
		i ++;
	}
	return (ft_substr(word, 0, i));
}

int	ft_dup_cmd(char **cmd, char **split_line, int *j, t_token t)
{
	if (t == none)
		*cmd = ft_strdup(*split_line);
	if (t == cmdnredirnfile)
		*cmd = ft_get_dep(*split_line);
	*j += 1;
	return (*j);
}

char	*ft_join_shrtct(char *str1, char *str2)
{
	char	*new_line;

	new_line = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (new_line);
}
