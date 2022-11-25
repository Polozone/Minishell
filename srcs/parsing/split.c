/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 09:25:00 by mgolinva          #+#    #+#             */
/*   Updated: 2022/10/10 16:24:47 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	t_var_quote	quote;
	int			i;

	i = 0;
	while ((str[i] && str[i] != set)
		|| (str[i] && str[i] == set
			&& ft_is_in_quote((char *)str, i, &quote) == true))
				i ++;
	return (i);
}

static int	ft_sep_count(char const *str, char sep)
{
	int			i;
	int			count;
	t_var_quote	quote;

	count = 0;
	i = 0;
	while (str[i])
	{
		while ((str[i] && str[i] == sep)
			|| (str[i] && str[i] == sep
				&& ft_is_in_quote((char *)str, i, &quote) == true))
			i ++;
		if (str[i] && str[i] != sep)
		{
			count ++;
			i ++;
		}
		while ((str[i] && str[i] != sep)
			|| (str[i] && str[i] == sep
				&& ft_is_in_quote((char *)str, i, &quote) == true))
			i ++;
	}
	return (count);
}

static char	**ft_actual_split(char **banana, char *s, char sep, int ct)
{
	int			i;
	int			j;
	t_var_quote	q;

	i = -1;
	j = 0;
	while (++i < ct && s[j])
	{
		while ((s[j] == sep && s[j])
			|| (s[j] && s[j] == sep && ft_is_in_quote((char *)s, j, &q) == 0))
			j ++;
		if (s[j] != sep && s[j])
		{
			banana[i] = ft_substr(s, j, ft_sprinkles_size(&s[j], sep));
			if (banana[i] == NULL)
				return (ft_free_split(banana, i));
			j ++;
		}
		while ((s[j] != sep && s[j])
			|| (s[j] && s[j] == sep && ft_is_in_quote((char *)s, j, &q) == 0))
			j ++;
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
	banana = malloc((count + 1) * sizeof(char *));
	if (!banana)
		exit (1);
	return (ft_actual_split(banana, str, sep, count));
}
