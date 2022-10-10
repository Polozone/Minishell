/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:07:23 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/10 11:59:46 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

void	pwd_to_envlst(t_prg *data, char *buf)
{
	if (buf == NULL)
	{
		ft_add_back_env_list(&data->env_lst,
			ft_lstnew_env_list(ft_strdup("PWD"),
				ft_get_env_var_content(data, "PWD")));
		free (buf);
	}
	else
		ft_add_back_env_list(&data->env_lst,
			ft_lstnew_env_list(ft_strdup("PWD"), getcwd(NULL, 0)));
}

void	ft_get_pwd(t_prg *data)
{
	t_env_lst	*tmp;
	char		*buf;

	tmp = data->env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD") == 0)
		{
			buf = getcwd(NULL, 0);
			if (buf != NULL)
			{
				free(buf);
				buf = tmp->content;
				tmp->content = getcwd(NULL, 0);
			}
			free (buf);
			return ;
		}
		tmp = tmp->next;
	}
	buf = getcwd(NULL, 0);
	pwd_to_envlst(data, buf);
}

void	ft_puterror_cd(t_prg *data, char *strerror, char *old_pwd)
{
	write(2, "cd: ", 4);
	ft_putstr_fd(strerror, 2);
	write(2, ": No such file or directory\n", 28);
	free(old_pwd);
	ft_get_pwd(data);
	g_error = 1;
}

int	_ch_dir(t_prg *data, char *old_pwd)
{
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		old_pwd = ft_get_env_var_content(data, "PWD");
	if (chdir_checks(data, old_pwd))
	{
		free(old_pwd);
		ft_get_pwd(data);
		return (0);
	}
	if (chdir(data->cmd_list->cmd_and_dep[1]) == -1)
	{
		ft_puterror_cd(data, data->cmd_list->cmd_and_dep[1], old_pwd);
		return (-1);
	}
	else
	{
		if (!_is_old_pwd(data, 1, old_pwd))
			ft_add_back_env_list(&data->env_lst,
				ft_lstnew_env_list(ft_strdup("OLDPWD"), ft_strdup(old_pwd)));
		else
			_is_old_pwd(data, 2, old_pwd);
	}
	ft_get_pwd(data);
	free(old_pwd);
	return (0);
}
