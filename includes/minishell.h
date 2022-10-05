/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmulin <pmulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:07:39 by mgolinva          #+#    #+#             */
/*   Updated: 2022/10/05 14:42:40 by pmulin           ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>
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
# define QUOTE_ERROR 5
# define PIPE_CHEV_ERROR 5

# define STDIN 0
# define STDOUT 1

typedef enum s_bool
{
	true,
	false
}				t_bool;

typedef enum s_token
{
	red,
	file,
	rednfile,
	cmdnredirnfile,
	none
}				t_token;

typedef enum s_builtin
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

typedef enum s_var_quote
{
	not_in_quote,
	in_single,
	in_double,
	in_both
}				t_var_quote;

typedef enum s_redir
{
	input,
	output,
	out_append,
	heredoc,
	error
}				t_redir;

typedef struct l_cmd_list
{
	char		**cmd_and_dep;
	t_bool		*has_been_exp;
	char		*path;
	char		**file;
	int			redir_nbr;
	t_redir		*redir_type;
	char		**heredoc_delimiter;
	t_builtin	is_cmd_builtin;
	int			infile;
	int			outfile;
	int			index;
	int			index_fd;
	int			*redir_fd;
	int			pipe_hd[2];
	void		*next;
}				t_cmd_lst;

typedef struct l_env_list
{
	char	*name;
	char	*content;
	void	*next;
}				t_env_lst;

typedef struct s_prg
{
	char			**path_list;
	char			**envp;
	char			**cells;
	char			*line;
	int				*pipe;
	int				*pid;
	int				heredoc_nbr;
	int				line_len;
	int				cmd_nbr;
	int				nbr_builtins;
	int				nbr_pid;
	t_cmd_lst		*cmd_list;
	t_env_lst		*env_lst;
	t_bool			is_there_path;
	t_bool			fork_capacity_met;
	struct termios	old_termios;
	struct termios	new_termios;
}					t_prg;

void			rl_replace_line(const char *text, int clear_undo);

/***** SIGNAUX.C *****/

void			setup_term(void);
void			handle_sigstp(int sig);

/***** STRING_SIZE.C *****/

int				ft_strlen(char *str);
int				ft_array_len(char **envp);
int				ft_strlen_2d(char **str);
int				ft_strlen_to_char(char *str, char c);

/***** STRING_REPRODUCTION.C *****/

char			*ft_strdup(char *str);
char			*ft_substr(char *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_backslash(char const *s1, char const *s2);
char			*ft_join_shrtct(char *str1, char *str2);
int				ft_dup_cmd(char **cmd, char **split_line, int j);

/***** STRING_SEARCH.C *****/

char			*ft_strstr(char *str, char *to_find);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				search_char(char *str, char c);
t_bool			ft_isalnum(int c);

/***** ITOA.C *****/

char			*ft_itoa(int nb);

/***** CMD_LIST.C *****/

void			ft_add_back_cmd_list(t_cmd_lst **alpha, t_cmd_lst *newb);
void			ft_lstclear_cmd_list(t_cmd_lst **lst);
t_cmd_lst		*ft_lstnew_cmd_list(void);
size_t			get_size_lst(t_prg *data);

/***** ENV_LIST.C *****/

t_env_lst		*ft_create_env_lst(char **envp, t_prg *prg);
t_env_lst		*ft_search_in_env_lst(t_prg *prg, char *name);
t_env_lst		*ft_last_env_list(t_env_lst *lst);
void			ft_add_back_env_list(t_env_lst **alpha, t_env_lst *newb);
t_env_lst		*ft_lstnew_env_list(char *name, char *content);
void			ft_make_elem(char *line, t_env_lst **env_lst, int index);
t_env_lst		*ft_search_in_env_lst(t_prg *prg, char *name);
t_env_lst		*ft_create_env_lst(char **envp, t_prg *prg);
int				_lst_size_env(t_env_lst *head);
t_env_lst		*ft_empty_env_lst(void);

/***** FILL_CMD_LST.C *****/

void			ft_fill_cmd_lst(t_prg *prg);
void			ft_find_path(t_prg *prg, t_cmd_lst *cmd_list);

/***** FILL_FILES.C *****/

void			ft_fill_file(t_cmd_lst *cmd_list, char **line_split,
					t_token *line_token, int len);

/***** FILL_NODES.C *****/

void			ft_fill_node(char *cell, t_cmd_lst *cmd_lst, t_prg *prg);

/***** TOKEN.C *****/

t_token			ft_redir_token(char *word);
t_token			*ft_assign_token(char **line_split, t_token *line_token, int i);
int				ft_count_token(t_token *line_token,
					t_token token_name, char **line_split, int len);

/***** SPLIT.C *****/

char			**ft_split(char *str, char sep);

/***** SPLIT_NO_QUOTES.C *****/

char			**ft_split_no_quotes(char const *str, char sep);

/***** PRINTF_FT.C *****/

void			ft_putstr_fd(char *str, int fd);
void			ft_putchar_fd(char c, int fd);

/***** PARSING.C *****/

void			ft_parse(t_prg *prg);

/***** QUOTE.C *****/

t_bool			ft_is_in_quote(char *line, int index, t_var_quote *quote);

/***** TRIM_QUOTE.C *****/

char			*ft_trim_quote(char *line);
char			*ft_extracted_phrase(char *line, int index, t_var_quote quote);
void			ft_quote_trimer(t_prg *prg, t_cmd_lst *buff);

/***** SYNTAX_ERROR.c *****/

t_bool			ft_syntax_error(t_prg *prg);

/***** CHEVRON_ERROR.c *****/

t_bool			ft_chevron_error(char *line, int line_len,
					char chevron, char che_two);

/***** BUILTIN_CHECK.C *****/

void			ft_is_cmd_builtin(t_prg *prg, t_cmd_lst *cmd_lst);

/***** REDIRECTIONS.C *****/

void			ft_redir_assignation(t_prg *prg, t_cmd_lst *cmd_lst,
					t_token *line_token, char **line_split);

/***** REPLACE_DOLLZ.C *****/

char			*ft_get_var_name(char *line, int index);
char			*ft_expend(t_prg *prg, char *line, int index);
t_bool			ft_is_phrase_a_file(char *line, int index,
					t_var_quote quote);
int				ft_char_is_dollz(t_prg *prg, char *line,
					char **new_line, int i);
void			ft_add_c_to_nl(t_var_quote quote, char **new_line,
					char *line, int i);

/***** REPLACE_DOLLZ.C *****/

char			*ft_forge_new_line(t_prg *prg, char *line);
char			*ft_forge_new_line_heredoc(t_prg *prg, char *line);

/***** FR_ATOI.C *****/

static long		ft_checker(long result, long neg);
int				ft_atoi(const char *str);
long long int	ft_atol(const char *str);
int				checker_lli(char *to_cmp);

/***** ENV.C *****/

void			_print_env_declare(t_prg *prg);

/***** ENV2.C *****/

int	_parsing_export(char *cmd, t_prg *prg);

/***** BUILTINS.C *****/

void			_print_env(t_env_lst *head);
void			_unset_env(t_prg *prg, size_t i, t_cmd_lst *node);
void			_unset_env_parent(t_prg *prg, t_cmd_lst *node);
int				_export_env(t_prg *prg, t_cmd_lst *node);
int				_export_env_parse(t_prg *prg);
void			_add_env(t_prg *prg, int i, int len);
int				_is_name_in_env(t_prg *prg, char *name_to_find);
void			_set_content_env(t_env_lst *node, char *content,
					char **content2d, int mode);
int				_echo_exe(t_cmd_lst *node, int i);
int				_pwd_exe(void);
int				_ch_dir(t_prg *data, char *old_pwd);
void			_add_node(char *name, char *content, t_prg *prg);
int				is_builtin_nofork(t_prg *data, t_cmd_lst *node);
int				is_builtin_fork(t_prg *data, t_cmd_lst *node);
int				count_builtins_nofork(t_cmd_lst *list);
void			env_to_tab(t_prg *prg, int i);
int				_exit_builtins(t_cmd_lst *node, int i, int len, long long exit_value);

/***** EXECUTIONS.C *****/

int				_ft_exe(t_prg *data);
void			_wait_pids(t_prg *data);
int				_execute_cmds(t_prg *data, size_t i, t_cmd_lst *tmp);
void			close_pipe(t_prg *data);
int				_set_fd(t_cmd_lst *tmp, t_prg *data);
void			_heredoc(t_prg *data, t_cmd_lst *tmp, int i);
void			_set_pipes(t_prg	*data, t_cmd_lst	*node);
char			*ft_strjoin_hd(char const *s1, char const *s2);
void			_init_heredoc(t_prg *data, int i, int pid);
void			check_heredoc(t_cmd_lst *tmp);
void			_close_pipe_hd(t_cmd_lst	*tmp, char *line, char *buf, int i);

/***** INIT_EXE.C *****/

int		_init_pipe(t_prg *data);
int		_alloc_exe_var(t_prg *data);
void	_set_index_list(t_prg *data);

/***** EXECUTIONS//IN_OUT_HANDLER.C*****/

int				_last_infile(t_cmd_lst *tmp);
int				_last_outfile(t_cmd_lst *tmp);
int				_is_infile(t_cmd_lst *tmp);
int				_is_outfile(t_cmd_lst *tmp);
void			_close_files(t_prg	*data, t_cmd_lst *node);
void			_open_all_outfile(t_cmd_lst *node);
int				is_file(const char *path);

/***** DUP_IN_OUT.C*****/

void	_set_dup_infile(t_cmd_lst *node);
void	_set_dup_outfile(t_cmd_lst *node, t_prg *data);

/***** ERROR_PRINT.C *****/

int				ft_error_print_one(t_cmd_lst *node,
					int error_code, char *error_source);
int				ft_error_print_two(t_cmd_lst *node,
					int error_code, char *error_source);
t_bool			ft_syntax_error_print(int error_code);

/***** FREE_EXECUTIONS.C *****/

void			_ft_free_exe(t_prg *data);
void			ft_free_1d(void	**to_free);
void			ft_free_2d(void	***to_free);
void			ft_free_char_array(char **array);
void			_ft_free_and_exit(t_prg *data);

/***** MEMORY_DEALLOC.C *****/

void			ft_free_parsing(t_prg *prg);
void			ft_free_env_lst(t_prg *prg);

/***** GET_NEXT_LINE.C *****/

char			*ft_strjoin_gnl(char *s1, char *s2, int i, int j);
char			*get_next_line(int fd);

/***** SIGNALS.C *****/

void			_sig_stp_main(int sig);
void			sig_handler_hd(void);
void			sig_parent(void);
void			sig_quit_exec(int signo);
void			sig_int_exec(int signo);

/***** EXECUTIONS//IN_OUT_HANDLER.C*****/

void			ft_update_shell_lvl(t_prg *data, int update);
void			change_termios(int action);

#endif