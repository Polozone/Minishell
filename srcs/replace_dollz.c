/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollz.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 08:26:55 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/25 17:35:38 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_dollz_ct(char *line)
{
	int	i;
	int	ct;

	i = 0;
	ct = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			ct ++;
		}
		i ++;
	}
	return (ct);	
}

char	*ft_get_var_name(char *line, int index)
{
	int	i;

	i = index + 1;
	while (line[i])
	{
		if (line[i] == '$' || line[i] == 34 || line[i] == 39)
		{
			i --;
			break;
		}
		i ++;
	}
	if (i == 0)
		return (NULL);
	return (ft_substr(line, index + 1, i - index));
}

int	ft_frst_q(char *line, int index, char q_type)
{
	int	i;

	i = index;
	while (i > 0 && line[i] != q_type)
		i --;
	return (i + 1);
}

int	ft_scnd_q(char *line, int index, char q_type)
{
	int	i;

	i = index;
	while (line[i] && line[i] != q_type)
		i ++;
	return (i - 1);	
}

char	*ft_strins(char *line, char *to_expend, int index)
{
	int	i;
	int	start;
	int end;

	i = index;
	start = 0;
	end = index;
	while (line[i] != '\'')
		i ++;
	while (line[start] && line[start] == '\"')
		start ++;
	while (line[end] && line[end] != '\"')
		end ++;
	printf("start = %d, end = %d, i = %d index = %d\n", start, end, i, index);
	return (ft_join_shortcut(ft_join_shortcut(ft_substr(line, start, index - start), ft_strdup(to_expend)), ft_substr(line, i, end - i)));
}

char	*ft_double_quoting(char	*line, char *to_expend, int index)
{
	int	i;
	int	qt_ct;
	int	start;
	int	end;

	i = index;
	qt_ct = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			qt_ct ++;
		if (qt_ct == 2)
		{
			end = i;
			break;
		}
		i ++;
	}
	while (--i > 0 && line[i] != line[end])
		;
	start = i;
	if (line[i] == '\'')
	{
		printf("test\n");
		return (ft_substr(line, start + 1, end - (start + 1)));
	}
	else if (line[i] == '\"')
		return (ft_strins(line, to_expend, index));
	return (NULL);
}

char	*ft_expend(t_prg *prg, char *line, int index, t_var_quote mark)
{
	t_env_lst	*env_lst;
	char		*var_name;
	char		*new_line;

	env_lst = prg->env_lst;
	var_name = ft_get_var_name(line, index);
	// printf("var_name = %s\n", var_name);
	while (env_lst != NULL)
	{
		if (ft_strcmp(env_lst->name, var_name) == 0)
		{
			if (mark == not_in_quote)
				new_line = ft_strdup(env_lst->content);
			if (mark == in_double)
				new_line = ft_strdup(env_lst->content);
			if (mark == in_single)
				new_line = ft_substr(line, ft_frst_q(line, index, '\''), ft_scnd_q(line, index, '\'') - ft_frst_q(line, index, '\'') + 1);
			if (mark == in_both)
				new_line = ft_double_quoting(line, env_lst->content,index);
			free(var_name);
			return (new_line);
		}
		env_lst = env_lst->next;
	}
	free(var_name);
	return (ft_strdup(""));
}

char	*ft_expend_or_not_expend(t_prg *prg, char *line, int index)
{
	if (ft_is_in_double(line, index) == false && ft_is_in_single(line, index) == false)
		return (ft_expend(prg, line, index, not_in_quote));
	else if (ft_is_in_double(line, index) == true && ft_is_in_single(line, index) == true)
		return (ft_expend(prg, line, index, in_both));
	else if (ft_is_in_double(line, index) == true && ft_is_in_single(line, index) == false)
		return (ft_expend(prg, line, index, in_double));
	else if (ft_is_in_double(line, index) == false && ft_is_in_single(line, index) == true)
		return (ft_expend(prg, line, index, in_single));
	return (NULL);
}

char	*ft_concatenate_array(char **new_lines, int new_lines_len)
{
	int		i;
	char	*new_line;

	i = 1;
	new_line = ft_strdup(new_lines[0]);
	while (new_lines[i] && i < new_lines_len)
	{
		new_line = ft_strjoin(new_line, new_lines[i]);
		i ++;
	}
	return (new_line);
}

char	*ft_forge_new_line(t_prg *prg, char *line)
{
	char	**new_lines;
	char	*new_line;
	int		new_lines_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_lines_len = ft_dollz_ct(line);
	new_lines = malloc((new_lines_len + 1) * sizeof(char *));
	while (line[i])
	{
		if (line[i] == '$')
		{
			new_lines[j] = ft_expend_or_not_expend(prg, line, i);
			// printf("j = %d, new_lines = %s\n", j, new_lines[j]);
			j ++;
		}
		i ++;
	}
	new_lines[j] = 0;
	new_line = ft_concatenate_array(new_lines, new_lines_len);
	ft_free_char_array(new_lines);
	return (new_line);
}