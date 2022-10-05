/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:57:27 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/05 11:57:35 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

void	_print_env(t_env_lst *head)
{
	t_env_lst	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->content)
		{
			printf("%s=", tmp->name);
			printf("%s\n", tmp->content);
		}
		tmp = tmp->next;
	}
}

void	_unset_env_parent(t_prg *prg, t_cmd_lst *node)
{
	size_t	i;
	size_t	lenght;

	i = 1;
	lenght = ft_strlen_2d(node->cmd_and_dep);
	while (i < lenght)
	{
		_unset_env(prg, i, node);
		i++;
	}
}

void	_unset_env(t_prg *prg, size_t i, t_cmd_lst *node)
{
	t_env_lst	*tmp;
	t_env_lst	*before;

	tmp = prg->env_lst;
	before = prg->env_lst;
	if (!ft_strcmp(node->cmd_and_dep[i], tmp->name))
	{
		free(prg->env_lst->name);
		free(prg->env_lst->content);
		free(prg->env_lst);
		prg->env_lst = ((t_env_lst *)prg->env_lst->next);
		return ;
	}
	while (tmp)
	{
		if (!ft_strcmp(node->cmd_and_dep[i], tmp->name))
		{
			free(tmp->name);
			free(tmp->content);
			free(tmp);
			before->next = tmp->next;
		}
		before = tmp;
		tmp = tmp->next;
	}
}

int	_parsing_export(char *cmd, t_prg *prg)
{
	int		i;

	if ((cmd[0] == '=') || (48 <= cmd[0] && cmd[0] <= 57))
	{
		printf("export: `%s': not a valid identifier\n", cmd);
		g_error = 1;
		return (1);
	}
	i = 0;
	while (cmd[i])
	{
		if (!((64 < cmd[i] && cmd[i] < 91) || (96 < cmd[i] && cmd[i] < 123)
				|| (47 < cmd[i] && cmd[i] < 58) || cmd[i] == '_'))
		{
			printf("export: `%s': not a valid identifier\n", cmd);
			g_error = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
