/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:07:39 by mgolinva          #+#    #+#             */
/*   Updated: 2022/05/18 14:34:19 by mgolinva         ###   ########.fr       */
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
# define ONE_RED 3
# define TWO_RED 4
# define SYNT_ER 5


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

typedef enum	s_redir
{
	input,
	output,
	out_append,
	heredoc
}				t_redir;

typedef struct l_cmd_list
{
	char		**cmd_and_dep;
	char		*path;
	char		**file;
	int			redir_nbr;
	t_redir		*redir_type;
	t_builtin	is_cmd_builtin;
	void		*next;
}				t_cmd_lst;

typedef struct	l_env_list
{
	char	*name;
	char	*content;
	void	*next;
}				t_env_lst;

typedef struct s_prg
{
	char		**envp;
	char		**cells;
	char		*line;
	int			line_len;
	int			cmd_nbr;
	t_cmd_lst	*cmd_list;
	t_env_lst	*env_lst;
	t_bool		is_there_path;
}			t_prg;

/***** STRING_MANIP.C *****/

int			ft_strlen(char *str);
char		*ft_strstr(char *str, char *to_find);
char		*ft_substr(char *s, unsigned int start, size_t len);
int			ft_array_len(char **envp);

/***** CMD_LIST.C *****/

void		ft_add_back_cmd_list(t_cmd_lst **alpha, t_cmd_lst *newb);
void		ft_lstclear_cmd_list(t_cmd_lst **lst);
t_cmd_lst	*ft_lstnew_cmd_list(void);

/***** ENV_LIST.C *****/

t_env_lst		*ft_create_env_lst(char **envp, t_prg *prg);
t_env_lst		*ft_search_in_env_lst(t_prg *prg, char *name);

/***** FILL_CMD_LST.C *****/

void		ft_fill_cmd_lst(t_prg *prg);

/***** SPLIT.C *****/

char		**ft_split(char *str, char sep);

/***** PRINTF_FT.C *****/

void		ft_putstr_fd(char *str, int fd);
void		ft_putchar_fd(char c, int fd);

/***** PARSING.C *****/

void		ft_parse(t_prg *prg);

/***** QUOTE.C *****/

t_bool		ft_is_in_single(const char *line, int index);
t_bool		ft_is_in_double(const char *line, int index);
t_bool		ft_is_in_quote(const char *line, int index);

/***** PIPE_ERROR.C *****/

t_bool		ft_syntax_error(t_prg *prg);

/***** BUILTIN_CHECK.C *****/

void		ft_is_cmd_builtin(t_prg *prg);

/***** REDIRECTIONS.C *****/

void		ft_redir_assignation(t_prg *prg);

#endif