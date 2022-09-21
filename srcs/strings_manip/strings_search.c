/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 11:26:43 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/21 17:37:00 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (str == 0)
		return (0);
	if (to_find[0] == '\0')
		return (str);
	while (str[i])
	{
		j = 0;
		while (str[i + j] && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (&str[i]);
			j ++;
		}
		i ++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while ((((unsigned char *)s1)[i] || ((unsigned char *)s2)[i]))
	{
		if (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
			i++;
		else
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	}
	return (0);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t  i;

    i = 0;
	if (!s1 || !s2)
		return (0);
    while ((((unsigned char *)s1)[i] || ((unsigned char *)s2)[i]) && i < n)
    {
        if (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
            i++;
        else
            return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
    }
    return (0);
}

int		search_char(char *str, char c)
{
	int		i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

t_bool	ft_isalnum(int c)
{
	if (c >= 48 && c <= 57)
		return (true);
	else if (c >= 65 && c <= 90)
		return (true);
	else if (c >= 97 && c <= 122)
		return (true);
	else
		return (false);
}
