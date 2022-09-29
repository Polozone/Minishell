/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_replace_dollz.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 08:26:55 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/29 12:58:55 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		else if (ft_isalnum(line[i]) == false && line[i] != '_')
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

	// if (line[index] == '\'' || line[index] == '\"')
	// 	i = index - 1;
	// else 
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
	return (i);	
}

static char	*ft_d_q_var(char *line, int index, char *content)
{
	char	*new_line;
	int		i;
	int		fst_qt;
	int		scd_qt;

	i = index + 1;
	new_line = NULL;
	fst_qt = ft_frst_q(line, index, '\"');
	scd_qt = ft_scnd_q(line, index, '\"');
	if (index !=  ft_frst_q(line, index, '\"'))
		new_line = ft_join_shrtct(ft_substr(line, fst_qt, (index - 1) - fst_qt), ft_strdup(content));
	else 
		new_line = ft_strdup(content);
	while (line[i] && ft_isalnum(line[i]) == true)
		i ++;
	if (i < scd_qt)
		new_line = ft_join_shrtct(new_line, ft_substr(line, i, scd_qt - i));
	return (new_line);
}

char	*ft_add_to_next_dollar(char *line, int index)
{
	int			i;
	int			next_dollz;
	t_var_quote	quote;

	i = index + 1;
	while ((line[i])
	&& (ft_isalnum(line[i]) == true || line[i] == '_'))
		i ++;
	printf("line = %s, i = %d\n", line, i);
	if (i == ft_strlen(line) || i == ft_strlen(line) - 1)
		return (ft_strdup(""));
	next_dollz = i;
	while (line[next_dollz] && line[next_dollz] != '$')
		next_dollz ++;
	printf("next_dollz = %d\n", next_dollz);
	if (next_dollz == 0)
		return (ft_strdup(""));
	printf("index = %d\n", index);
	ft_is_in_quote(line, next_dollz, &quote);
	int k = i;
	while (line[k] != )
	// LE PB EST DANS LES LIGNES QUI SUIVENT, UNE MAUVAIS UTIL DE SUBSTR SANS DOUTE
	if (quote == in_single)
	{
		printf("il est passe pqr ici\n");
		return (ft_substr(line, i, ft_frst_q(line, i, '\'')) - i);
	}
	else if (quote == in_double)
		return (ft_substr(line, i, ft_frst_q(line, i, '\"')) - 1);
	else
	{
		printf("JAMBON\n");
		return (ft_substr(line, i, next_dollz - i));
	}
}

char	*ft_expend(t_prg *prg, char *line, int index, t_var_quote quote_type)
{
	//LE PB VIENT DE L'INDEX QUI NE CHANGE PAS D'UNE ITERATION A L'AUTRE
	t_env_lst	*env_lst;
	char		*var_name;
	char		*new_line;

	env_lst = prg->env_lst;
	var_name = ft_get_var_name(line, index);
	printf("var_name = %s\n", var_name);
	new_line = NULL;
	if (quote_type == in_single)
	{
		printf("test\n");
		new_line = ft_substr(line, ft_frst_q(line, index, '\''),
		ft_scnd_q(line, index, '\'') - ft_frst_q(line, index, '\''));
		return (ft_join_shrtct(new_line, ft_add_to_next_dollar(line, index)));
	}
	while (env_lst != NULL)
	{
		if (ft_strcmp(env_lst->name, var_name) == 0)
		{
			if (quote_type == not_in_quote)
				new_line = ft_join_shrtct(ft_strdup(env_lst->content), ft_add_to_next_dollar(line, index));
			else if (quote_type == in_double)
				new_line = ft_d_q_var(line, index, env_lst->content);
			free(var_name);
			return (new_line);
		}
		env_lst = env_lst->next;
	}
	if (quote_type == in_double)
		return (ft_d_q_var(line, index, ""));
	return (ft_strdup(""));
}

char	*ft_expend_or_not_expend(t_prg *prg, char *line, int index)
{
	t_var_quote quote;

	if (ft_is_in_quote(line, index, &quote) == false)
		return (ft_expend(prg, line, index, quote));
	else if (ft_is_in_quote(line, index, &quote) == true)
		return (ft_expend(prg, line, index, quote));
	return (NULL);
}

char	*ft_add_line_start(char *line)
{
	int			i;
	int			fst_q;
	t_var_quote	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (ft_is_in_quote(line, i, &quote) == false)
				return (NULL);
			if (quote == in_single)
				fst_q = ft_frst_q(line, i, '\'');
			else if (quote == in_double)
				fst_q = ft_frst_q(line, i, '\"');
			break;
		}
		i ++;
	}
	if (fst_q > 1)
		return (ft_substr(line, 0, fst_q - 1));
	else
		return (NULL);
}

char	*ft_concatenate_array(char **new_lines, int new_lines_len, char *line)
{
	int			i;
	char		*new_line;
	
	new_line = ft_add_line_start(line);
	// printf("test %s\n", new_line);
	if (new_line == NULL)
	{
		new_line = ft_strdup(new_lines[0]);
		i = 1;
	}
	else
		i = 0;
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
			j ++;
		}
		i ++;
	}
	new_lines[j] = 0;
	new_line = ft_concatenate_array(new_lines, new_lines_len, line);
	ft_free_char_array(new_lines);
	return (new_line);
}