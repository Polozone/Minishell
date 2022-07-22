/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollz.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:23:29 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/22 15:48:26 by mgolinva         ###   ########.fr       */
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

int	*ft_get_dollz_index(char *line)
{
	int	i;
	int j;
	int	*dollz_index_array;

	i = 0;
	j = 0;
	dollz_index_array = malloc((ft_dollz_ct(line) + 1) * sizeof(dollz_index_array));
	if (dollz_index_array == NULL)
		exit(0);
	while (line[i])
	{
		if (line[i] == '$')
		{
			printf("i = %d j = %d\n", i, j);
			dollz_index_array[j] = i;
			j ++;
		}
		i ++;
	}
	return (dollz_index_array);
}

char	*ft_get_word(char *line, int index, char c)
{
	int		i;
	char	*word;

	i = 0;
	printf("LINE IN GET WORD = %s\n", line);
	while (line[i])
	{
		printf("line[%d] = %c\n", i, line[i]);
		if (line[i] == c || i == ft_strlen(line) || line[i] == 34 || line[i] == 39)
		{
			word = ft_substr(line, 0, i);
			return (word);
		}
		i ++;
	}
	return (ft_strdup(line));
}

char	*ft_expender(t_prg *prg, char *line)
{
	int			i;
	char		*word;
	t_env_lst	*env_lst_buff;

	i = 0;
	env_lst_buff = prg->env_lst;
	while (env_lst_buff != NULL)
	{
		word = ft_get_word(line, 1, '$');
		// printf("WORD = %s\n", word);
		if (ft_strcmp(env_lst_buff->name, word) == 0)
		{
			free(word);
			return (ft_strdup(env_lst_buff->content));
		}
		free(word);
		env_lst_buff = env_lst_buff->next;
	}
	return (ft_strdup(""));
}

t_bool	ft_dollz_is_first(char *line)
{
	int	i;
	i = 0;
	while ((line[i])
	&& (line[i] == 34 || line[i] ==39))
		i ++;
	if (line[i] == '$')
		return (true);
	return (false);
}

char	*ft_forge_new_line(t_prg *prg, int *dollz_index, char *line)
{
	char		*new_line;
	char		*buff;
	char		*append;
	int			index_nbr;
	int			i;

	i = 0;
	index_nbr = ft_dollz_ct(line);
	new_line = NULL;
	if (ft_is_in_single(line, dollz_index[i]) == true && ft_dollz_is_first(line) == true)
	{
		new_line = ft_get_word(line/*[dollz_index[i]]*/,dollz_index[i], '\''); 
		i ++;
	}
	else if (new_line == NULL && dollz_index[i] == 0)
	{
		new_line = ft_expender(prg, line);
		i ++;
	}
	else if (new_line == NULL)
	{
		new_line = ft_get_word(line, 0, '$');
		// printf("in forge new_line = %s\n", new_line);
	}
	while (i < index_nbr)
	{
		// printf("dollz_index[%d] = %d is it in single = %d\n", i, dollz_index[i], ft_is_in_single(line, dollz_index[i]));
		if (ft_is_in_single(line, dollz_index[i]) == true)
		{
			buff = new_line;
			append = ft_get_word(line, dollz_index[i - 1], '\''); 
			printf("TEEEEEEEEEEEEEEEEEEEEST APPEND = %s\n", append);
			new_line = ft_strjoin(new_line, append);
			// free(buff);
			// free(append);
		}
		else
		{
			buff = new_line;
			append = ft_expender(prg, &line[dollz_index[i]]);
			// printf("APPEND = %s\n", append);
			new_line = ft_strjoin(new_line, append);
			// free(buff);
			// free(append);
		}
		i ++;
	}
	return (new_line);
}

char	*ft_replace_dollz(t_prg *prg, char *line)
{
	int		*dollz_index_array;
	char	*new_line;

	dollz_index_array = ft_get_dollz_index(line);
	new_line = ft_forge_new_line(prg, dollz_index_array, line);
	// printf("new_line = %s\n", new_line);
	// for(int i = 0; i < ft_dollz_ct(line); i++)
	// 	printf("index %d = %d\n", i, dollz_index_array[i]);
	// ft_free_int_array(dollz_index_array);
	// free(line);
	return (new_line);
 }