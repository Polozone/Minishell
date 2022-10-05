/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:16:48 by pmulin            #+#    #+#             */
/*   Updated: 2022/10/05 10:16:28 by pmulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_pwd_exe(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		perror("");
	printf("%s\n", path);
	free(path);
	return (0);
}
