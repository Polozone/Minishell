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
# include <termios.h>

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
	char		**cmd_and_dep;	// command and his flags ___ exemple => (s1)unset (s2)variable
	char		*path;			// path to the command (extract of PATH= in env variables)
	char		**file;			// duble char array of each files -> infile and outfile (wrtie at the last outfile)
	int			redir_nbr;		// nbr on redirections
	t_redir		*redir_type;	// enum to know the nature of the redirection
	t_builtin	is_cmd_builtin; // enum to know if the command is a builtins and the nature of the builtins.
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
	char		**envp;		// envp variables
	char		**cells; 	// return of split(); take the content of each pipe in a string
	char		*line;   	// return of readline(); take the prompt
	int			line_len;	// lenght of *line;
	int			cmd_nbr; 
	t_cmd_lst	*cmd_list; 	// pointer on the head of the t_cmd_lst;
	t_env_lst	*env_lst; 	// pointer on the head of the t_env_lst;
	t_bool		is_there_path;
}			t_prg;

/***** STRING_MANIP.C *****/

int				ft_strlen(char *str);
char			*ft_strstr(char *str, char *to_find);
char			*ft_substr(char *s, unsigned int start, size_t len);
int				ft_array_len(char **envp);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strlen_2d(char **str);
int				ft_strcmp(const char *s1, const char *s2);

/***** CMD_LIST.C *****/

void			ft_add_back_cmd_list(t_cmd_lst **alpha, t_cmd_lst *newb);
void			ft_lstclear_cmd_list(t_cmd_lst **lst);
t_cmd_lst		*ft_lstnew_cmd_list(void);

/***** ENV_LIST.C *****/

t_env_lst			*ft_create_env_lst(char **envp, t_prg *prg);
t_env_lst			*ft_search_in_env_lst(t_prg *prg, char *name);
t_env_lst			*ft_last_env_list(t_env_lst *lst);
void				ft_add_back_env_list(t_env_lst **alpha, t_env_lst *newb);
t_env_lst			*ft_lstnew_env_list(char *name, char *content);
void				ft_make_elem(char *line, t_env_lst **env_lst, int index);
t_env_lst			*ft_search_in_env_lst(t_prg *prg, char *name);
t_env_lst			*ft_create_env_lst(char **envp, t_prg *prg);


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

/***** BUILTINS.C *****/

void		_print_env(t_env_lst *head);
void		_unset_env(t_prg *prg, size_t i);
void		_unset_env_parent(t_prg *prg);
int			_export_env(t_prg *prg);
int			_export_env_parse(t_prg *prg);
void		_lst_add_env(t_prg *prg, int i, int boole, char **result);
int			_is_name_in_env(t_prg *prg, char *name_to_find);
void		_set_content_env(t_env_lst *node, char *content, char **content2d, int mode);
int			_echo_exe(t_prg *data, int i);
int			_pwd_exe();
int			_ch_dir(t_prg *data);

/***** EXECUTIONS.C *****/

void _ft_execution(t_prg prg);


#endif