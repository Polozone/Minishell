/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:19:43 by pmulin            #+#    #+#             */
/*   Updated: 2021/12/03 18:14:38 by pmulin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_buf(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

static void	after_nl(char *buf)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buf[i] != '\n' && buf[i])
		i++;
	i++;
	while (buf[i])
	{
		buf[j] = buf[i];
		j++;
		i++;
	}
	buf[j] = '\0';
}

static int	security_ret(int ret, char *line)
{
	if (ret == -1)
	{
		free(line);
		return (-1);
	}
	return (0);
}

static int	security_line(char *line)
{
	if (line == NULL || line[0] == 0)
	{
		free(line);
		return (-1);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char		buf[11] = {0};
	char			*line;
	int				ret;

	line = NULL;
	ret = 1;
	if (fd < 0)
		return (NULL);
	while (ret > 0)
	{
		line = ft_strjoin_gnl(line, buf, -1, 0);
		if (check_buf(buf) == 0)
		{
			after_nl(buf);
			return (line);
		}
		ret = read(fd, buf, 10);
		if (security_ret(ret, line) == -1)
			return (NULL);
		buf[ret] = '\0';
	}
	if (security_line(line) == -1)
		return (NULL);
	return (line);
}

// int main()
// {
// 	printf("%s", get_next_line(open("fichier.txt", O_RDWR)));
// 	return (0);
// }

// int main()
// {
// 	int fdbible = open("alternate_line_nl_with_nl", O_RDWR);
// 	printf("fdbible == %d", fdbible);
// 	int fd = open("test.txt", O_RDWR);
// 	printf("fd == %d", fd);
// 	char *str;
// 	//ft_putstr_fd("sdssd", 3);
// 	str = get_next_line(fdbible);
// 	while (str)
// 	{
// 		ft_putstr_fd(str, 4);
// 		printf("%s", str);
// 		free(str);
// 		str = get_next_line(fdbible);
// 	}
// 	close(fd);
// 	return (0);
// }
