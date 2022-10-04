/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:59:48 by mgolinva          #+#    #+#             */
/*   Updated: 2022/09/30 16:11:58 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_lst	*ft_last_env_list(t_env_lst *lst)
{
	void	*p;

	if (lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		p = lst;
		lst = lst->next;
	}
	return (p);
}

void	ft_add_back_env_list(t_env_lst **alpha, t_env_lst *newb)
{
	t_env_lst	*tmp;

	if (!alpha || !newb)
		return ;
	else if (!*alpha)
	{
		*alpha = newb;
		return ;
	}
	else
	{
		tmp = ft_last_env_list(*alpha);
		tmp->next = newb;
	}
}

t_env_lst	*ft_lstnew_env_list(char *name, char *content)
{
	t_env_lst	*env;

	env = malloc(sizeof(t_env_lst));
	if (env == NULL)
		exit (1);
	env->name = name;
	env->content = content;
	env->next = NULL;
	return (env);
}

void	ft_make_elem(char *line, t_env_lst **env_lst, int index)
{
	int		i;
	int		j;
	char	*name;
	char	*content;

	i = 0;
	j = 0;
	while (line[i] != '=')
		i ++;
	name = ft_substr(line, 0, i);
	j = i;
	while (line[j])
		j ++;
	content = ft_substr(line, i + 1, j);
	if (index == 0)
		*env_lst = ft_lstnew_env_list(name, content);
	else
		ft_add_back_env_list(env_lst, ft_lstnew_env_list(name, content));
}

t_env_lst	*ft_empty_env_lst(void)
{
	t_env_lst	*env;

	env = ft_lstnew_env_list(ft_strdup("PWD"), getcwd(NULL, 0));
	ft_add_back_env_list(&env, ft_lstnew_env_list(ft_strdup("SHLVL"), ft_strdup("0")));
	ft_add_back_env_list(&env, ft_lstnew_env_list(ft_strdup("_"), ft_strdup("/usr/bin/env")));
	return (env);
}

t_env_lst	*ft_create_env_lst(char **envp, t_prg *prg)
{
	int	i;

	i = 1;
	if (&envp[0][0] == NULL)
		return (ft_empty_env_lst());
	ft_make_elem(envp[0], &prg->env_lst, 0);
	while (envp[i])
	{
		ft_make_elem(envp[i], &prg->env_lst, i);
		i ++;
	}
	return (prg->env_lst);
}
