/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:16:48 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/10 16:27:56 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_pwd_exe(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("");
		exit (1);
	}
	printf("%s\n", path);
	free(path);
	return (1);
}
