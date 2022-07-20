
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/minishell.h"

void _print_env(t_env_lst *head)
{
	t_env_lst *tmp;

	tmp = head;
	while (tmp != NULL)
	{
		printf("%s", tmp->name);
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

void	_unset_env_parent(t_prg *prg)
{
	size_t	i;
	size_t	lenght;

	i = 1;
	lenght = ft_strlen_2d(prg->cmd_list->cmd_and_dep);
	while (i < lenght)
	{
		_unset_env(prg, i);
		i++;
	}
}

void	_unset_env(t_prg *prg, size_t i)
{
	t_env_lst *tmp;
	t_env_lst *before;

	tmp = prg->env_lst;
	prg->env_lst = tmp;
	if (!ft_strncmp(prg->env_lst->name, ft_strjoin(prg->cmd_list->cmd_and_dep[i], "="), ft_strlen(prg->env_lst->name)))
	{
		prg->env_lst = ((t_env_lst*)prg->env_lst->next);
		return ;
	}
	while (prg->env_lst != NULL)
	{
		if (!ft_strncmp(prg->env_lst->name, ft_strjoin(prg->cmd_list->cmd_and_dep[i], "="), ft_strlen(prg->env_lst->name)))
		{
			before->next = ((t_env_lst*)prg->env_lst->next);
			break ;
		}
		before = prg->env_lst;
		prg->env_lst = prg->env_lst->next;
	}
	prg->env_lst = tmp;
}

void	_set_content_env(t_env_lst *node, char *content, char **content2d, int mode)
{
	if (mode == 1)
	{
		if (content[0] == ' ')
			node->content = "";
		else
			node->content = content;
	}
	else
	{
		if (content[0] == ' ')
			ft_add_back_env_list(&node, ft_lstnew_env_list(ft_strjoin(content2d[0], "="), ""));
		else
			ft_add_back_env_list(&node, ft_lstnew_env_list(ft_strjoin(content2d[0], "="), content2d[1]));
	}

}

void	_lst_add_env(t_prg *prg, int i, int boole, char **result)
{
	t_env_lst *ptr_to_head;
	t_env_lst *tmp;

	ptr_to_head = prg->env_lst;
	tmp = prg->env_lst;
	while (prg->cmd_list->cmd_and_dep[++i])
	{
		result = ft_split(prg->cmd_list->cmd_and_dep[i], '='); // I WILL HAVE TO FREE THAT 2D ARRAY FOR EACH ITERATION
		boole = 0;
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, ft_strjoin(result[0], "="))) // if the variable we want to add is already in ENV
			{
				_set_content_env(tmp, result[1], NULL, 1);
				boole = 1;
			}
			tmp = tmp->next;
		}
		if (boole != 1)
			_set_content_env(ptr_to_head, result[1], result, 42);
		tmp = prg->env_lst;
	}
}

int		_export_env(t_prg *prg)
{
	//_export_env_parse(prg);
	char **result;
	_lst_add_env(prg, 0, 0, result);
	return (0);
}