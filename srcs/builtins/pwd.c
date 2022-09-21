
#include "../../includes/minishell.h"

int		_pwd_exe()
{
	char *path;
	// path = malloc(1016 * sizeof(char) + 1);
	path = getcwd(NULL, 0);
	if (path == NULL)
		perror("");
	// dprintf(2, "\nTEST1\n");
	printf("%s\n", path);
	// dprintf(2, "\nTEST2\n");
	free(path);
	return (0);
}