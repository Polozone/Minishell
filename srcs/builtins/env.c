/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:12:16 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/10 09:15:45 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

void	_add_env(t_prg *prg, int i, int len, t_cmd_lst *node)
{
	char	*name;
	char	*content;
	int		sep;

	len = ft_strlen_2d(node->cmd_and_dep) - 1;
	while (node->cmd_and_dep[++i])
	{
		sep = ft_strlen_to_char(node->cmd_and_dep[i], '=');
		if (sep)
			name = ft_substr(node->cmd_and_dep[i], 0, sep);
		else
			name = ft_strdup(node->cmd_and_dep[i]);
		if (i == 1 && (name[0] == '#' || name[0] == '$'))
		{
			_print_env_declare(prg);
			return ;
		}
		if (_parsing_export(name, prg, node->cmd_and_dep[i]))
			i++;
		if (i > len)
			break ;
		content = ft_substr(node->cmd_and_dep[i], sep + 1,
				ft_strlen(node->cmd_and_dep[i]) - sep);
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

int	_is_env(t_prg *data, char *name)
{
	t_env_lst	*tmp;

	tmp = data->env_lst;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	_export_env(t_prg *prg, t_cmd_lst *node)
{
	int		i;

	i = 0;
	while (node->cmd_and_dep[++i])
	{
		if (_is_env(prg, node->cmd_and_dep[i]) == 0)
			_add_env(prg, 0, 0, node);
	}
	return (0);
}
