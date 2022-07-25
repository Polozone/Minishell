/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:07:39 by mgolinva          #+#    #+#             */
/*   Updated: 2022/07/20 13:47:30 by mgolinva         ###   ########.fr       */
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

typedef enum	s_token
{
	red,
	file,
	rednfile,
	none
}				t_token;

typedef enum	s_builtin
{
	not_built_in, //egale a zero si il n y a pas de builtins, sinon valeur de 1 a 7
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
	heredoc,
	error
}				t_redir;

typedef struct l_cmd_list
{
	char		**cmd_and_dep;	// command and his flags ___ exemple => (s1)unset (s2)variable
	char		*path;			// path to the command (extract of PATH= in env variables)
	char		**file;			// duble char array of each files -> infile and outfile (write at the last outfile)
	int			redir_nbr;		// nbr on redirections
	t_redir		*redir_type;	// enum to know the nature of the redirection
	char		*heredoc_delimiter; //the heredoc delimiter
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
	char		**path_list;
	char		**envp;
	char		**cells;
	char		*line;
	int			*pipe;
	int			*pid;
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
char		*ft_strdup(char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_backslash(char const *s1, char const *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strlen_2d(char **str);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_free_char_array(char **array);
int			search_char(char *str, char c);
int			ft_strlen_to_char(char *str, char c);
// void		ft_free_array(void array, int len);

/***** CMD_LIST.C *****/

void			ft_add_back_cmd_list(t_cmd_lst **alpha, t_cmd_lst *newb);
void			ft_lstclear_cmd_list(t_cmd_lst **lst);
t_cmd_lst		*ft_lstnew_cmd_list(void);
size_t			get_size_lst(t_prg *data);

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

/***** FILL_NODES.C *****/

void				ft_fill_node(char *cell, t_cmd_lst *cmd_lst, t_prg *prg);

/***** TOKEN.C *****/


t_token				ft_redir_token(char *word);
t_token				*ft_assign_token(char **line_split, t_token *line_token);
int					ft_count_token(t_token *line_token, t_token token_name, int len);

/***** SPLIT.C *****/

char				**ft_split(char *str, char sep);

/***** SPLIT_NO_QUOTES.C *****/

char				**ft_split_no_quotes(char const *str, char sep);

/***** PRINTF_FT.C *****/

void				ft_putstr_fd(char *str, int fd);
void				ft_putchar_fd(char c, int fd);

/***** PARSING.C *****/

void		ft_parse(t_prg *prg);

/***** QUOTE.C *****/

t_bool		ft_is_in_single(const char *line, int index);
t_bool		ft_is_in_double(const char *line, int index);
t_bool		ft_is_in_quote(const char *line, int index);

/***** PIPE_ERROR.C *****/

t_bool		ft_syntax_error(t_prg *prg);

/***** BUILTIN_CHECK.C *****/

void		ft_is_cmd_builtin(t_prg *prg, t_cmd_lst *cmd_lst);

/***** REDIRECTIONS.C *****/

void		ft_redir_assignation(t_prg *prg, t_cmd_lst *cmd_lst, t_token *line_token, char **line_split);

/***** BUILTINS.C *****/

void		_print_env(t_env_lst *head);
void		_unset_env(t_prg *prg, size_t i);
void		_unset_env_parent(t_prg *prg);
int			_export_env(t_prg *prg);
int			_export_env_parse(t_prg *prg);
void		_add_env(t_prg *prg, int i);
int			_is_name_in_env(t_prg *prg, char *name_to_find);
void		_set_content_env(t_env_lst *node, char *content, char **content2d, int mode);
int			_echo_exe(t_prg *data, int i);
int			_pwd_exe();
int			_ch_dir(t_prg *data);
void		_add_node(char *name, char *content, t_prg *prg);

/***** EXECUTIONS.C *****/

void		_ft_exe(t_prg *data);
void		_wait_pids(t_prg data);
int			_execute_cmds(t_prg *data, size_t i);

/***** FREE_EXECUTIONS.C *****/

void		_ft_free_exe(t_prg *data);


#endif