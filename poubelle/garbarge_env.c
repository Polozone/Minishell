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

int	*ft_get_dollz_index(int *dollz_index_list, char *line)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			dollz_index_list[j] = i;
			j ++;
		}
		i ++;
	}
	return (dollz_index_list);
}

char	*ft_get_word(char *line, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (line[i])
	{
		if (line[i] == c || line[i] == '"' || line[i] == 39)
		{
			word = ft_substr(line, 0, i);
			return (word);
		}
		i ++;
	}
	return (ft_strdup(line));
}

char	**ft_fill_env_var_array(t_prg *prg, int *dollz_i_lst, char *line, int dollz_nbr)
{
	int			i;
	t_env_lst	*env_lst_buff;
	char		**env_var_array;
	char		*word;

	i = 0;
	env_var_array = malloc((dollz_nbr + 1) * sizeof(char *));
	while (i < dollz_nbr)
	{
		env_lst_buff = prg->env_lst;
		while (env_lst_buff != NULL)
		{
			word = ft_get_word(&line[dollz_i_lst[i] + 1], '$');
			if (ft_strcmp(env_lst_buff->name, word) == 61)
			{
				free(word);
				break;
			}
			free(word);
			env_lst_buff = env_lst_buff->next;
		}
		if (ft_is_in_quote(line, dollz_i_lst[i]) == true || env_lst_buff == NULL)
			if (i < dollz_nbr)
				env_var_array[i] = ft_substr(line, dollz_i_lst[i], dollz_i_lst[i + 1]);
			else 
				env_var_array[i] = ft_strdup(&line[dollz_i_lst[i]]);
		else
			env_var_array[i] = ft_strdup(env_lst_buff->content);
		printf("ARRAY[%d] = %s\n", i, env_var_array[i]);
		i ++;
	}
	env_var_array[i] = 0;
	return (env_var_array);
}

char	*ft_recreate_line(char *line, char **array)
{
	int		i;
	char	*buff;
	char	*new_line;
	
	i = -1;
	new_line = NULL;
	if (line[0] == 39 && line[ft_strlen(line) - 1] == 39)
		return (ft_strdup(line));
	while (array[++i])
	{
		if (array[i][0] == '$')
			new_line = ft_strdup("");
		else if (i == 0 && line[0] != '$')
		{
			new_line = ft_get_word(&line[0], '$');
			buff = new_line;
			new_line = ft_strjoin(new_line, array[i]);
			free(buff);
		}
		else if (i == 0)
			new_line = ft_strdup(array[i]);
		else // (ft_is_in_quote(array[i], 0) && array[i][0] != '$')
		{
			buff = new_line;
			new_line = ft_strjoin(new_line, array[i]);
			free(buff);
		}
	}
	return (new_line);
}

static char	*ft_replace_dollzzz(t_prg *prg, char *line, int dollz_i)
{
	int 	*dollz_index_list;
	int		dollz_nbr;
	char	**env_var_array;
	char	*expended_line;

	dollz_nbr = ft_dollz_ct(line);
	dollz_index_list = malloc ((dollz_nbr + 1) * sizeof(dollz_index_list));
	dollz_index_list = ft_get_dollz_index(dollz_index_list, line);
	env_var_array = ft_fill_env_var_array(prg, dollz_index_list, line, dollz_nbr);
	expended_line = ft_recreate_line(line, env_var_array);
	free(dollz_index_list);
	ft_free_char_array(env_var_array);
	return (expended_line);
}

t_bool	ft_is_there_dollzzz(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (true);
		i ++;
	}
	return (false);
}