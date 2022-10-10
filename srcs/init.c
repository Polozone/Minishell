/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:03:42 by mgolinva          #+#    #+#             */
/*   Updated: 2022/10/10 16:22:55 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_to_tab(t_prg *prg, int i)
{
	t_env_lst	*tmp;
	int			size_lst;
	char		*tmp_name;

	size_lst = _lst_size_env(prg->env_lst);
	prg->envp = malloc((sizeof(char *)) * size_lst + 1);
	if (!prg->envp)
		exit (1);
	tmp = prg->env_lst;
	while (tmp)
	{
		tmp_name = ft_strjoin(tmp->name, "=");
		if (tmp->content == NULL)
			prg->envp[i] = ft_strjoin(tmp_name, ft_strdup(""));
		else
			prg->envp[i] = ft_strjoin(tmp_name, tmp->content);
		tmp = tmp->next;
		i++;
		free(tmp_name);
	}
	prg->envp[i] = 0;
}

static void	_init_exe_var(t_prg *data)
{
	data->pid = NULL;
	data->pipe = NULL;
	data->fork_capacity_met = false;
	data->has_heredoc_been_sig_ended = false;
}

void	ft_init(char **env, t_prg *prg)
{
	prg->env_lst = ft_create_env_lst(env, prg);
	ft_update_shell_lvl(prg, 1);
	_init_exe_var(prg);
	tcgetattr(0, &prg->old_termios);
	prg->new_termios = prg->old_termios;
	prg->new_termios.c_lflag &= ~ECHOCTL;
}
