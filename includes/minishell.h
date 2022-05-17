/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:07:39 by mgolinva          #+#    #+#             */
/*   Updated: 2022/05/17 11:02:56 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ONE_PIPE 1
# define TWO_PIPE 2
# define ONE_RED 1
# define TWO_RED 2

int	g_error;

typedef enum	s_bool
{
	true,
	false
}				t_bool;

typedef enum	s_builtin
{
	not_built_in,
	echo,
	cd,
	pwd,
	export,
	unset,
	env,
	quit
}				t_builtin;

typedef struct s_prg
{
	char		**env_p;
	char		**path;
	char		**cells;
	char		***cmd_list;
	char		*line;
	int			line_len;
	int			cmd_nbr;
	t_builtin	*is_cmd_builtin;
	t_bool		is_there_path;
}			t_prg;

/***** STRING_MANIP.C *****/

int			ft_strlen(const char *str);
char		*ft_strstr(char *str, char *to_find);
char		*ft_substr(const char *s, unsigned int start, size_t len);

/***** SPLIT.C *****/

char		**ft_split(char *str, char sep);

/***** PATH_LIST_MAKER.C *****/

char		**ft_path_list_maker(char **envp, t_prg *prg);
int			ft_array_len(char **envp);

/***** PRINTF_FT.C *****/

void		ft_putstr_fd(char *str, int fd);
void		ft_putchar_fd(char c, int fd);

/***** PARSING.C *****/

void		ft_parse(t_prg *prg);

/***** QUOTE.C *****/

t_bool		ft_is_in_quote(const char *line, int index);

/***** PIPE_ERROR.C *****/

t_bool		ft_pipe_error(char *line, int line_len);

/***** BUILTIN_CHECK.C *****/

void		ft_is_cmd_builtin(t_prg *prg);

#endif