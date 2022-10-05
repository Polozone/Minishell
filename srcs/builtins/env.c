/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:12:16 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/05 11:57:24 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

void	_add_node(char *name, char *content, t_prg *prg)
{
	t_env_lst	*tmp;
	char		*tmp_line;

	tmp = prg->env_lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			tmp_line = tmp->content;
			tmp->content = content;
			free(tmp_line);
			tmp_line = tmp->name;
			tmp->name = name;
			free(tmp_line);
			return ;
		}
		tmp = tmp->next;
	}
	ft_add_back_env_list(&prg->env_lst, ft_lstnew_env_list(name, content));
}

void	_add_env(t_prg *prg, int i, int len)
{
	char	*name;
	char	*content;
	int		sep;

	len = ft_strlen_2d(prg->cmd_list->cmd_and_dep) - 1;
	while (prg->cmd_list->cmd_and_dep[++i])
	{
		sep = ft_strlen_to_char(prg->cmd_list->cmd_and_dep[i], '=');
		if (sep)
			name = ft_substr(prg->cmd_list->cmd_and_dep[i], 0, sep);
		else
			name = ft_strdup(prg->cmd_list->cmd_and_dep[i]);
		if (i == 1 && (name[0] == '#' || name[0] == '$'))
		{
			_print_env_declare(prg);
			return ;
		}
		if (_parsing_export(name, prg))
			i++;
		if (i > len)
			break ;
		content = ft_substr(prg->cmd_list->cmd_and_dep[i], sep + 1,
				ft_strlen(prg->cmd_list->cmd_and_dep[i]) - sep);
		_add_node(name, content, prg);
	}
}

void	_print_env_declare(t_prg *prg)
{
	t_env_lst	*tmp;

	tmp = prg->env_lst;
	while (tmp)
	{
		printf("declare -x %s", tmp->name);
		if (tmp->content)
			printf("=\"%s\"", tmp->content);
		printf("\n");
		tmp = tmp->next;
	}
}

int	_lst_size_env(t_env_lst *head)
{
	t_env_lst	*tmp;
	int			i;

	tmp = head;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	_export_env(t_prg *prg, t_cmd_lst *node)
{
	_add_env(prg, 0, 0);
	return (0);
}
