
#include "../../includes/minishell.h"

void	is_builtin(t_prg data)
{
	if (data.cmd_list->is_cmd_builtin)
		if (data.cmd_list->is_cmd_builtin == echo)
			_echo_exe(&data, 0);
		if (data.cmd_list->is_cmd_builtin == cd)
			_ch_dir(&data);
		if (data.cmd_list->is_cmd_builtin == pwd)
			_pwd_exe();
		if (data.cmd_list->is_cmd_builtin == export)
			_export_env(&data);
		if (data.cmd_list->is_cmd_builtin == unset)
			_unset_env_parent(&data);
		if (data.cmd_list->is_cmd_builtin == env)
			_print_env(data.env_lst);
		if (data.cmd_list->is_cmd_builtin == quit)
			exit(0);
}

void _ft_exe(t_prg data)
{
	int i = 0;
	is_builtin(data);
	if (data.cmd_list->cmd_and_dep != NULL)
	{
		while (data.cmd_list->cmd_and_dep[i])
		{
			//printf("%s\n", data.cmd_list->cmd_and_dep[i]);
			i++;
		}
	}
}