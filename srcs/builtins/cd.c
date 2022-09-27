
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../includes/minishell.h"

int		_is_old_pwd(t_prg *data, int mode, char* old_pwd)
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
	else
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, "OLDPWD"))
				tmp->content = old_pwd;
			tmp = tmp->next;
		}
	}
	return (0);
}

int		_ch_dir(t_prg *data)
{
	char	*old_pwd;

	old_pwd = malloc((sizeof(char) * 1016) + 1); // FREE CETTE VARIABLE AU BESOIN + CHECK AVEC MAX FT_lstnew_env_list si on malloc dedans
	if (old_pwd == NULL)
	{
		// TOUT FREE + EXIT PAR FONCTION
		exit (0);
	}
	getcwd(old_pwd, 1016);
	if (chdir(data->cmd_list->cmd_and_dep[1]) == -1)
	{
		perror("");
		return (-1);
	}
	else
		if (!_is_old_pwd(data, 1, old_pwd))
			ft_add_back_env_list(&data->env_lst, ft_lstnew_env_list("OLDPWD", old_pwd));
		else
			_is_old_pwd(data, 2, old_pwd);
	return (0);
}