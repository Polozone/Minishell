
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/minishell.h"

void    _echo_exe(t_prg *data)
{
    int     i;

    if(!ft_strcmp(data->cmd_list->cmd_and_dep[1], "-n"))
        i = 2;
    else
        i = 1;
    while (data->cmd_list->cmd_and_dep[i++])
        printf("%s", data->cmd_list->cmd_and_dep[i]);
}