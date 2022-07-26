
#include "../../includes/minishell.h"

void	close_pipe(t_prg *data)
{
	int		i;

	i = 0;
	while (i < (data->cmd_nbr - 1) * 2)
	{
		close(data->pipe[i]);
		i++;
	}
}

// < infile cat | wc -l > outfile666 | cat infile2 > outfile3

// cat infile | wc -l >> outfile66

// < infile cat | wc -l >> outfile666

// < infile cat > outfile666

// < infile cat > outfile666 | ls > outfile2 > outfile3 > outfile4

void	_init_fd(t_prg *data)
{
	t_cmd_lst	*tmp;
	
	tmp = data->cmd_list;
	while (tmp)
	{
		tmp->infile = 0;
		tmp->outfile = 1;
		tmp = tmp->next;
	}
}

int		_last_infile(t_cmd_lst *tmp)
{
	int		i;

	i = 0;
	while (i < tmp->redir_nbr && tmp->redir_type[i] == 0)
		i++;
	return (i);
}

int		_last_outfile(t_cmd_lst *tmp)
{
	int		i;
	int		buffer;

	i = 0;
	buffer = 0;
	while (i < tmp->redir_nbr)
	{
		if (tmp->redir_type[i] == 1 || tmp->redir_type[i] == 2)
			buffer = i;
		i++;
	}
	return (buffer);
}

int		_is_infile(t_cmd_lst *tmp)
{
	int		i;

	i = 0;
	while (i < tmp->redir_nbr)
	{
		if (tmp->redir_type[i] == 0)
			return (1);
		i++;
	}
	return (0);
}

int		_is_outfile(t_cmd_lst *tmp)
{
	int		i;

	i = 0;
	while (i < tmp->redir_nbr)
	{
		if (tmp->redir_type[i] == 1 || tmp->redir_type[i] == 2)
			return (1);
		i++;
	}
	return (0);
}

void	_ft_execve(t_prg *data)
{
	int i = 0;

}

void	_set_fd(t_cmd_lst *tmp, t_prg *data)
{
	_init_fd(data);
	if (_is_infile(tmp))
	{
		tmp->infile = open(tmp->file[_last_infile(tmp) - 1], O_RDWR);
		int check = dup2(tmp->infile, 0);
		printf("\ncheck == %d\n", check);
	}
	if (_is_outfile(tmp))
	{
		tmp->outfile = open(tmp->file[_last_outfile(tmp)], O_CREAT | O_RDWR, 0644);
		int check = dup2(tmp->outfile, 1);
		printf("\ncheck == %d\n", check);
	}
	// dprintf(1, "CECI EST UN TEST");
	_ft_execve(data);
	// _last_infile(tmp);
	
	// printf("redir nbr == %d (%s)", tmp->redir_nbr, tmp->cmd_and_dep[0]);
	// while (i < tmp->redir_nbr)
	// {
	// 	printf("(%s)redir type == %d\n", tmp->cmd_and_dep[0], tmp->redir_type[i]);
	// 	i++;
	// }
	// printf("\n\n\n");
	return ;
}

int		_execute_cmds(t_prg *data, size_t i, t_cmd_lst *tmp)
{
	_set_fd(tmp, data);
	close_pipe(data);
	exit(0);
	return (0);
}