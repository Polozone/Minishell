
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/minishell.h"

int		_pwd_exe()
{
	char *path;
	path = malloc(1016 * sizeof(char) + 1);
	path = getcwd(path, 1016);
	if (path == NULL)
		perror("");
	printf("%s\n", path);
	free(path);
	return (0);
}