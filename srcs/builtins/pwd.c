
#include "../../includes/minishell.h"

int		_pwd_exe()
{
	char *path;
	// path = malloc(1016 * sizeof(char) + 1);
	path = getcwd(NULL, 0);
	if (path == NULL)
		perror("");
	printf("%s\n", path);
	free(path);
	return (0);
}