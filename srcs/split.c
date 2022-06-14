/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 09:25:00 by mgolinva          #+#    #+#             */
/*   Updated: 2022/05/18 15:22:38 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**ft_free_split(char **banana, int i)
{
	while (i >= 0)
	{
		free(banana[i]);
		i --;
	}
	free(banana);
	return (0);
}

static int	ft_sprinkles_size(const char *str, char set)
{
	int	i;

	i = 0;
	while ((str[i] && str[i] != set)
	|| (str[i] && str[i] == set && ft_is_in_quote(str, i) == true))
		i ++;
	return (i);
}

static int	ft_sep_count(char const *str, char sep)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while ((str[i] && str[i] == sep)
		|| (str[i] && str[i] == sep && ft_is_in_quote(str, i) == true))
			i ++;
		if (str[i] && str[i] != sep)
		{
			count ++;
			i ++;
		}
		while ((str[i] && str[i] != sep)
		|| (str[i] && str[i] == sep && ft_is_in_quote(str, i) == true))
			i ++;
	}
	return (count);
}

static char	**ft_actual_split(char **banana, char *str, char sep, int ct)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ct && str[j])
	{
		while ((str[j] == sep && str[j])
		|| (str[j] && str[j] == sep && ft_is_in_quote(str, j) == true))
			j ++;
		if (str[j] != sep && str[j])
		{
			banana[i] = ft_substr(str, j, ft_sprinkles_size(&str[j], sep));
			if (ft_is_in_quote(str, i) == false)
				;
			if (banana[i] == NULL)
				return (ft_free_split(banana, i));
			j ++;
		}
		while ((str[j] != sep && str[j])
		|| (str[j] && str[j] == sep && ft_is_in_quote(str, j) == true))
			j ++;
		i ++;
	}
	banana[i] = 0;
	return (banana);
}

char	**ft_split(char *str, char sep)
{
	int		count;
	char	**banana;

	if (!str)
		return (0);
	count = ft_sep_count(str, sep);
	banana = malloc((count + 1) * sizeof(char **));
	if (!banana)
		exit (0);
	return (ft_actual_split(banana, str, sep, count));
}
