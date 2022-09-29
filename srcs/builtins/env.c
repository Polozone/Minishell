
#include "../../includes/minishell.h"

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

void _unset_env_parent(t_prg *prg, t_cmd_lst *node)
{
	size_t i;
	size_t lenght;

	i = 1;
	lenght = ft_strlen_2d(node->cmd_and_dep);
	while (i < lenght)
	{
		_unset_env(prg, i, node);
		i++;
	}
}

void _unset_env(t_prg *prg, size_t i, t_cmd_lst *node)
{
	t_env_lst	*tmp;
	t_env_lst	*before;

	tmp = prg->env_lst;
	before = prg->env_lst;
	if (!ft_strcmp(node->cmd_and_dep[i], tmp->name))
	{
		prg->env_lst = ((t_env_lst*)prg->env_lst->next);
		return ;
	}
	while (tmp)
	{
		if (!ft_strcmp(node->cmd_and_dep[i], tmp->name))
			before->next = tmp->next;
		before = tmp;
		tmp = tmp->next;
	}
}

int _parsing_export(char *cmd, t_prg *prg)
{
	int		i;

	i = 0;
	if (cmd[0] == '#' || cmd[0] == '$')
	{
		_print_env_declare(prg);
		return (0);
	}
	if ((cmd[0] == '=') || (48 <= cmd[0] && cmd[0] <= 57))
	{
		printf("export: `%s': not a valid identifier\n", cmd);
		return (1);
	}
	while (cmd[i])
	{
		if ((61 > cmd[i]) || (61 < cmd[i] && cmd[i] < 65) || (90 < cmd[i] && cmd[i] < 97) || (cmd[i] > 122))
		{
			printf("export: `%s': not a valid identifier\n", cmd);
			return (1);
		}
		i++;
	}
	return (0);
}

void _add_node(char *name, char *content, t_prg *prg)
{
	t_env_lst *tmp;

	tmp = prg->env_lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			tmp->content = content;
			return;
		}
		tmp = tmp->next;
	}
	ft_add_back_env_list(&prg->env_lst, ft_lstnew_env_list(name, content));
}

void _add_env(t_prg *prg, int i)
{
	char *name;
	char *content;
	int sep;
	int	len;

	len = ft_strlen_2d(prg->cmd_list->cmd_and_dep) - 1;
	while (prg->cmd_list->cmd_and_dep[++i])
	{
		if (_parsing_export(prg->cmd_list->cmd_and_dep[i], prg))
			i++;
		if (i > len)
			break ;
		sep = ft_strlen_to_char(prg->cmd_list->cmd_and_dep[i], '=');
		name = ft_substr(prg->cmd_list->cmd_and_dep[i], 0, sep);
		content = ft_substr(prg->cmd_list->cmd_and_dep[i], sep + 1, ft_strlen(prg->cmd_list->cmd_and_dep[i]) - sep);
		_add_node(name, content, prg);
	}
}

void _print_env_declare(t_prg *prg)
{
	t_env_lst *tmp;

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

int _lst_size_env(t_env_lst *head)
{
	t_env_lst *tmp;
	int i;

	tmp = head;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int _export_env(t_prg *prg, t_cmd_lst *node)
{
	if (strcmp(node->cmd_and_dep[0], "export") == 0 && node->cmd_and_dep[1] == NULL)
	{
		_print_env_declare(prg);
		return (0);
	}
	_add_env(prg, 0);
	return (0);
}