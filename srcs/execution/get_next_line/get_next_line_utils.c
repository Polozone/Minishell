/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:19:53 by pmulin            #+#    #+#             */
/*   Updated: 2021/12/03 16:19:55 by pmulin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_strjoin_gnl(char *s1, char *s2, int i, int j)
{
	char		*str;
	int			len_s1;
	int			len_s2;

	if (s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	str = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (++i < len_s1)
		str[i] = s1[i];
	while ((s2[j] != '\n') && (j < len_s2))
		str[i++] = s2[j++];
	if (s2 && s2[j] == '\n')
		str[i++] = s2[j];
	str[i] = '\0';
	free(s1);
	return (str);
}
