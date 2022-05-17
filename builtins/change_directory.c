
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_env	t_env;

struct s_env {
	char	*env_var;
	t_env	*next;
};

int		ft_strlen(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

t_env	*ft_lstlast(t_env *lst)
{
	t_env	*ptr;

	ptr = lst;
	if (!lst)
		return (NULL);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	ft_lstadd_back(t_env **alst, t_env *new)
{
	t_env	*last;

	last = ft_lstlast((*alst));
	if (alst == NULL)
		return ;
	if ((*alst) == NULL)
	{
		(*alst) = new;
		new->next = NULL;
		return ;
	}
	last->next = new;
}

t_env	*ft_lstnew(void *content)
{
	t_env	*element;

	element = malloc(sizeof(t_env));
	if (element == NULL)
		return (NULL);
	element->env_var = content;
	element->next = NULL;
	return (element);
}

void	pwd()
{
	char *buf;

	buf = malloc(1024 * sizeof(char));
	if (getcwd(buf, 1024) == NULL)
		perror("");
	printf("%s", buf);
	free(buf);
}

void	change_dir(char *path)
{
	if (chdir(path) == -1)
		perror("");
	printf("\n");
}

void	ft_env(t_env *env)
{
	t_env *tmp;
	tmp = env;

	while (tmp != NULL)
	{
		printf("%s\n", tmp->env_var);
		tmp = tmp->next;
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((((unsigned char *)s1)[i] || ((unsigned char *)s2)[i]) && i < n)
	{
		if (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
			i++;
		else
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	}
	return (0);
}


void	init_env(char **envp, t_env **env)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(env, ft_lstnew(envp[i]));
		i++;
	}
}

void	ft_unset(t_env *env, char *variable)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->env_var, variable, ft_strlen(variable) == 0))
		{
			printf("%s\n", tmp->env_var);
		}
		tmp = tmp->next;
	}
}

int main(int ac, char **av, char **envp)
{
	t_env	*env;

	env = NULL;
	init_env(envp, &env);
	ft_unset(env, "LESS=-R");
	return (0);
}
