/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_charset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:27:48 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/21 09:46:10 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_is_charset(char str, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (str == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	count_arrays(char *str, char *charset)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_is_charset(str[i], charset) && str[i])
			i ++;
		while ((!ft_is_charset(str[i], charset) && str[i])
		|| (i > 0 && i < ft_strlen(str)))
			j ++;
		if (!ft_is_charset(str[i], charset) && str[i])
			i ++;
	}
	return (j);
}

static int	ft_strlen_split(char *str, char *charset, int index)
{
	int	ct;

	ct = 0;
	while (str[index] && ft_is_charset(str[index], charset) == 0)
	{
		index ++;
		ct ++;
	}
	return (ct);
}

static char	*ft_strdup_charset_split(char *str, char *charset, int index)
{
	int		i;
	int		t;
	char	*dest;

	dest = 0;
	i = 0;
	t = ft_strlen_split(str, charset, index);
	dest = malloc((t + 1) * sizeof(char));
	if (!dest)
		return (0);
	while (i < index + t && ft_is_charset(str[index], charset) == 0
		&& (str[index]))
	{
		dest[i] = str[index];
		i ++;
		index ++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split_charset(char *str, char *charset)
{
	char	**split;
	int		i;
	int		ct_string;

	i = 0;
	ct_string = 0;
	split = malloc((count_arrays(str, charset) + 1) * sizeof(split));
	if (charset == 0)
	{
		split = malloc(2 * sizeof(split));
		split [0] = ft_strdup_charset_split(str, "", 0);
		split [1] = 0;
		return (split);
	}
	while (ct_string < count_arrays(str, charset))
	{
		while (ft_is_charset(str[i], charset) == 1 && str[i])
			i ++;
		if (ft_is_charset(str[i], charset) == 0)
			split[ct_string++] = ft_strdup_charset_split(str, charset, i);
		while (ft_is_charset(str[i], charset) == 0 && str[i])
			i ++;
	}
	split[ct_string] = 0;
	return (split);
}