/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:07:23 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/05 11:54:39 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

int	_is_old_pwd(t_prg *data, int mode, char *old_pwd)
{
	t_env_lst	*tmp;

	tmp = data->env_lst;
	if (mode == 1)
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, "OLDPWD"))
				return (1);
			tmp = tmp->next;
		}
		return (0);
	}
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "OLDPWD"))
		{
			free(tmp->content);
			tmp->content = ft_strdup(old_pwd);
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*get_home_path(t_prg *data)
{
	t_env_lst	*tmp;
	char		*buf;

	tmp = data->env_lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "HOME"))
		{
			buf = ft_strdup(tmp->content);
			return (buf);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	chdir_checks(t_prg *data, char *old_pwd)
{
	char	*path_home;

	if (!data->cmd_list->cmd_and_dep[1])
	{
		path_home = get_home_path(data);
		if (path_home == NULL)
		{
			write(2, "cd: HOME not set\n", 17);
			g_error = 1;
			return (1);
		}
		chdir(path_home);
		free(path_home);
		if (!_is_old_pwd(data, 1, old_pwd))
			ft_add_back_env_list(&data->env_lst,
				ft_lstnew_env_list("OLDPWD", old_pwd));
		else
			_is_old_pwd(data, 2, old_pwd);
		return (1);
	}
	return (0);
}

int	_ch_dir(t_prg *data, char *old_pwd)
{
	old_pwd = getcwd(NULL, 0);
	if (chdir_checks(data, old_pwd))
	{
		free(old_pwd);
		return (0);
	}
	if (chdir(data->cmd_list->cmd_and_dep[1]) == -1)
	{
		write(2, "cd: ", 4);
		ft_putstr_fd(data->cmd_list->cmd_and_dep[1], 2);
		write(2, ": No such file or directory\n", 28);
		free(old_pwd);
		return (-1);
	}
	else
	{
		if (!_is_old_pwd(data, 1, old_pwd))
			ft_add_back_env_list(&data->env_lst,
				ft_lstnew_env_list("OLDPWD", old_pwd));
		else
			_is_old_pwd(data, 2, old_pwd);
	}
	free(old_pwd);
	return (0);
}
