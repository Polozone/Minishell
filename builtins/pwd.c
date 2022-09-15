
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
	// dprintf(2, "111\n");
	printf("%s\n", path);
	// dprintf(2, "222\n");
	free(path);
	return (0);
}