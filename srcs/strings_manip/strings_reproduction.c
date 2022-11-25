/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_reproduction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:33:22 by mgolinva          #+#    #+#             */
/*   Updated: 2022/10/10 16:27:03 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup(char *str)
{
	int		i;
	int		size;
	char	*dub;

	if (!str)
		return (NULL);
	i = 0;
	size = ft_strlen(str);
	dub = malloc((size + 1) * sizeof(char));
	if (!dub)
		exit (1);
	while (str[i])
	{
		dub[i] = str[i];
		i++;
	}
	dub[i] = '\0';
	return (dub);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	size;
	char			*ditto;

	if (!s)
		return (0);
	if (start > (unsigned int)ft_strlen(s))
		return (0);
	i = start;
	j = 0;
	size = ft_strlen(s) - start;
	if (size > len)
		size = len;
	ditto = malloc((size + 1) * sizeof(char));
	if (!ditto)
		exit (1);
	while (j < size)
	{
		ditto[j] = s[i];
		i++;
		j++;
	}
	ditto[j] = '\0';
	return (ditto);
}

char	*ft_strjoin_hd(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	j = 0;
	i = -1;
	if (!s2)
		return (NULL);
	str = malloc((ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1) * sizeof(char));
	if (str == NULL)
		exit (1);
	while (++i < ft_strlen((char *)s1))
		str[i] = s1[i];
	while (j < ft_strlen((char *)s2))
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free((void *)s1);
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1) * sizeof(char));
	if (str == NULL)
		exit (1);
	while (i < ft_strlen((char *)s1))
	{
		str[i] = s1[i];
		i++;
	}
	while (j < ft_strlen((char *)s2))
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin_backslash(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	j = -1;
	i = -1;
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 2) * sizeof(char));
	if (str == NULL)
		exit (1);
	while (++i < ft_strlen((char *)s1))
		str[i] = s1[i];
	str[i] = '/';
	i++;
	while (++j < ft_strlen((char *)s2))
	{
		str[i] = s2[j];
		i++;
	}
	str[i] = '\0';
	return (str);
}
