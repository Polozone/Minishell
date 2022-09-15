/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_shortcut_fts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:02:20 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/14 17:09:49 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_join_shrtct(char *str1, char *str2)
{
	char	*new_line;
	new_line = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (new_line);
}