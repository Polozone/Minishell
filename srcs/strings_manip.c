/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_manip.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 11:26:43 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/25 16:05:56 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*void	ft_close(int fd1, int fd2)
{
	if (close(fd1) < 0)
		return (perror("close : "));
	else if (close(fd2) < 0)
		return (perror("close : "));
}*/


int	ft_array_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i ++;
	return (i);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i ++;
	return (i);
}

int ft_strlen_2d(char **str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

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
		return (0);
	while (j < size)
	{
		ditto[j] = s[i];
		i ++;
		j ++;
	}
	ditto[j] = '\0';
	return (ditto);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*str;
	size_t		i;
	size_t		j;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1)
			* sizeof(char));
	if (str == NULL)
		return (NULL);
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((((unsigned char *)s1)[i] || ((unsigned char *)s2)[i]))
	{
		if (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
			i++;
		else
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	}
	return (0);
}

void	ft_free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i ++;
	}
	free(array);
}



int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t  i;

    i = 0;
    while ((((unsigned char *)s1)[i] || ((unsigned char *)s2)[i]) && i < n)
    {
        if (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
            i++;
        else
            return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
    }
    return (0);
}

/*void	ft_free_array(void **array, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(array[i]);
		i ++;
	}
	free(array);
}*/

char    *ft_strjoin_backslash(char const *s1, char const *s2)
{
    char        *str;
    size_t      i;
    size_t      j;

    j = -1;
    i = -1;
    if (!s1 || !s2)
        return (NULL);
    str = malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 2)
            * sizeof(char));
    if (str == NULL)
        return (NULL);
    while (++i < ft_strlen((char *)s1))
        str[i] = s1[i];
	str[i] = '/';
	i ++;
    while (++j < ft_strlen((char *)s2))
    {
        str[i] = s2[j];
        i++;
    }
    str[i] = '\0';
    return (str);
}

char	*ft_strdup(char *str)
{
	int		i;
	int		size;
	char	*dub;

	i = 0;
	size = ft_strlen(str);
	dub = malloc((size + 1) * sizeof(char));
	if (!dub)
		return (0);
	while (str[i])
	{
		dub[i] = str[i];
		i ++;
	}
	dub[i] = '\0';
	return (dub);
}