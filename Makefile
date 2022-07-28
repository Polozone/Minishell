SRCS =	srcs/main.c				\
		srcs/split.c			\
		srcs/split_charset.c	\
		srcs/strings_manip.c	\
		srcs/printing_ft.c		\
		srcs/quote.c			\
		srcs/syntax_error.c		\
		srcs/builtin_check.c	\
		srcs/cmd_list.c			\
		srcs/env_list.c			\
		srcs/fill_cmd_lst.c		\
		srcs/fill_nodes.c		\
		srcs/fill_files.c		\
		srcs/redirections.c		\
		srcs/token.c			\
		srcs/replace_dollz.c	\
		srcs/parsing.c			\
		srcs/utilis_shortcut_fts.c	\
		builtins/env.c			\
		builtins/echo.c			\
		builtins/cd.c			\
		builtins/pwd.c			\
		srcs/execution/ft_free_execution.c			\
		srcs/execution/ft_execution.c	\
		srcs/execution/_execute_cmds.c

OBJS = $(SRCS:.c=.o)

INCL =	includes/minishell.h

CC = gcc

RM = rm -f

#FLAGS = -lreadline -Wall -Werror -Wextra -fsanitize=address -g3

FLAGS = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -Wall -Werror -Wextra -fsanitize=address -g3

%.o.c: $(INCL) Makefile
	$(CC) $(FLAGS) -c $< -o $@

NAME = minishell

$(NAME): $(OBJS) $(INCL) Makefile
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: make clean fclean all re