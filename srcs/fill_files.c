/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:46:45 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/27 13:54:07 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_multiple_files_line(char **files, char *line, int *files_ct)
{
	int	i;
	int next_chev;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			while (line[i] == '>' || line[i] == '<')
				i ++;
			next_chev = i;
			while ((line[next_chev])
			&& (line[next_chev] != '>' && line[next_chev] != '<'))
			{
				next_chev ++;
			}
			files[*files_ct] = ft_substr(line, i, next_chev - i);
			*files_ct += 1;
		}
		if (line[i] == 0)
			break;
		i ++;
	}
}

void	ft_fill_file(t_cmd_lst *cmd_list, char **line_split,
t_token *line_token, int len)
{
	int	i;
	int	file_ct;
	int file_nbr;

	i = 0;
	file_nbr = ft_count_token(line_token, red, line_split, len)
	+ ft_count_token(line_token, rednfile, line_split, len);
	file_ct = 0;
	cmd_list->file = malloc((file_nbr + 1) * sizeof(char *));
	if (!cmd_list->file)
		exit(1);
	while (i < len)
	{
		if (line_token[i] == file)
		{
			cmd_list->file[file_ct] = ft_strdup(line_split[i]);
			file_ct ++;
		}
		else if (line_token[i] == rednfile)
			ft_multiple_files_line(cmd_list->file, line_split[i], &file_ct);
		i ++;
	}
	cmd_list->file[file_ct] = 0;
}