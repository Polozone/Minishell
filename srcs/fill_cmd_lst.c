/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:42:27 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/20 16:25:53 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_create_path_list(t_prg *prg)
{
	t_env_lst *buff;

	buff = prg->env_lst;
	while (buff != 0)
	{
		if (ft_strncmp(buff->name, "PATH=", 5) == 0)
		{
			prg->is_there_path = true;
			break;
		}
		buff = buff->next;
		prg->is_there_path = false;
	}
	if (prg->is_there_path == true)
		prg->path_list = ft_split(buff->content, ':');
}

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

void	ft_get_dollz_index(int **dollz_index_list, char *line)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (line[i])
	{
		printf("test\n");
		if (line[i] == '$')
		{
			*dollz_index_list[j] = i;
			j ++;
		}
		i ++;
	}
}

char	**ft_fill_env_var_array(t_prg *prg, int *dollz_i_lst, char *line, int dollz_nbr)
{
	int			i;
	t_env_lst	*env_lst_buff;
	char		**env_var_array;

	i = 0;
	env_var_array = malloc((dollz_nbr + 1) * sizeof(char *));
	while (i < dollz_nbr)
	{
		env_lst_buff = prg->env_lst;
		while (env_lst_buff != NULL)
		{
			if (ft_strcmp(env_lst_buff->name, &line[dollz_i_lst[i] + 1]) == 61)
				break;
			env_lst_buff = env_lst_buff->next;
		}
		if (ft_is_in_single(line, dollz_i_lst[i]) == true || env_lst_buff == NULL)
			if (i < dollz_nbr)
				env_var_array[i] = ft_substr(line, dollz_i_lst[i], dollz_i_lst[i + 1]);
			else 
				env_var_array[i] = ft_strdup(&line[dollz_i_lst[i]]);
		else
			env_var_array[i] = ft_strdup(env_lst_buff->content);
		i ++;
	}
	env_var_array[i] = 0;
	return (env_var_array);
}

char	*ft_recreate_line(char **array)
{
	int		i;
	int		len;
	char	*buff;
	char	*new_line;
	
	i = 0;
	len = ft_array_len(array);
	new_line = NULL;
	while (array[i])
	{
		if (i == 0)
			new_line = ft_strdup(array[i]);
		else
		{
			buff = new_line;
			new_line = ft_strjoin(new_line, array[i]);
			free(buff);
		}
		i ++;
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
	dollz_index_list = malloc ((dollz_nbr + 1) * sizeof(int));
	ft_get_dollz_index(&dollz_index_list, line);
	env_var_array = ft_fill_env_var_array(prg, dollz_index_list, line, dollz_nbr);
	expended_line = ft_recreate_line(env_var_array);
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

void	ft_expend_env_variable(t_prg *prg, t_cmd_lst *cmd_lst)
{
	int	i;
	int	dollz_i;
	char *buff;

	i = 0;
	if (cmd_lst->cmd_and_dep == 0)
		return;
	while (cmd_lst->cmd_and_dep[i])
	{
		if (ft_is_there_dollzzz(cmd_lst->cmd_and_dep[i]) == true)
		{
		buff = cmd_lst->cmd_and_dep[i];
		cmd_lst->cmd_and_dep[i] =
		ft_replace_dollzzz(prg, cmd_lst->cmd_and_dep[i], dollz_i);
		free(buff);
		}
		i ++;
	}
}

void	ft_fill_cmd_lst(t_prg *prg)
{
	int	i;
	t_cmd_lst *buff;

	i = 0;
	buff = prg->cmd_list;
	ft_create_path_list(prg);
	while (prg->cells[i])
	{
		ft_fill_node(prg->cells[i], buff, prg);
		ft_expend_env_variable(prg, buff);
		i ++;
		buff = buff->next;
	}
	t_cmd_lst *buff2 = prg->cmd_list;
	
	while (buff2)
	{
		if (buff2->cmd_and_dep != 0)
			for (int i = 0; buff2->cmd_and_dep[i]; i ++)
				printf("cmd_n_dep[%d] = %s\n", i, buff2->cmd_and_dep[i]);
		printf("path= %s\n", buff2->path);
		if (buff2->file != 0)
			for (int i = 0; buff2->file[i]; i ++)
				printf("file[%d] = %s\n", i, buff2->file[i]);
		if (buff2->redir_nbr != 0)			
			printf("redir_nbr = %d\n", buff2->redir_nbr);
		if (buff2->redir_type != 0)
			for (int i = 0; i < buff2->redir_nbr; i ++)
				printf("redir_type[%d] = %u\n", i, buff2->redir_type[i]);
		if (buff2->is_cmd_builtin != 0)
			printf("is_cmd_builtin = %d\n", buff2->is_cmd_builtin);
		if (buff2->heredoc_delimiter != 0)
			printf("heredoc truc = %s\n", buff2->heredoc_delimiter);
		buff2 = buff2->next;
	}
	// ft_free_array(prg->path_list);
}
