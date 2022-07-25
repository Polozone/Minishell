
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
		if (tmp->content)
		{
			printf("%s=", tmp->name);
			printf("%s\n", tmp->content);
		}
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

int		_parsing_export(char *cmd)
{
	if (cmd[0] == '=')
	{
		printf("export: `%s': not a valid identifier\n", cmd);
		return (1);
	}
	return (0);
}

void	_add_node(char *name, char *content, t_prg *prg)
{
	t_env_lst	*tmp;

	tmp = prg->env_lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			tmp->content = content;
			return ;
		}
		tmp = tmp->next;
	}
	ft_add_back_env_list(&prg->env_lst, ft_lstnew_env_list(name, content));
}

void	_add_env(t_prg *prg, int i)
{
	char	*name;
	char	*content;
	int		sep;

	while (prg->cmd_list->cmd_and_dep[++i])
	{
		if (_parsing_export(prg->cmd_list->cmd_and_dep[i]))
			i++ ;
		sep = ft_strlen_to_char(prg->cmd_list->cmd_and_dep[i], '=');
		name = ft_substr(prg->cmd_list->cmd_and_dep[i], 0, sep);
		content = ft_substr(prg->cmd_list->cmd_and_dep[i], sep + 1, ft_strlen(prg->cmd_list->cmd_and_dep[i]) - sep);
		_add_node(name, content, prg);
	}
}

void	_print_env_declare(t_prg *prg)
{
	t_env_lst* tmp;

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

int		_export_env(t_prg *prg)
{
	if (strcmp(prg->cmd_list->cmd_and_dep[0], "export") == 0 && prg->cmd_list->cmd_and_dep[1] == NULL)
	{
		_print_env_declare(prg);
		return (0);
	}
	_add_env(prg, 0);
	return (0);
}