SRCS =	srcs/main.c				\
		srcs/parsing/split.c			\
		srcs/parsing/split_charset.c	\
		srcs/parsing/strings_manip.c	\
		srcs/parsing/printing_ft.c		\
		srcs/parsing/quote.c			\
		srcs/parsing/trim_quote.c		\
		srcs/parsing/syntax_error.c		\
		srcs/parsing/builtin_check.c	\
		srcs/parsing/cmd_list.c			\
		srcs/parsing/env_list.c			\
		srcs/parsing/fill_cmd_lst.c		\
		srcs/parsing/fill_nodes.c		\
		srcs/parsing/fill_files.c		\
		srcs/parsing/redirections.c		\
		srcs/parsing/token.c			\
		srcs/parsing/replace_dollz.c	\
		srcs/parsing/parsing.c			\
		srcs/parsing/utilis_shortcut_fts.c	\
		srcs/parsing/error_print.c		\
		srcs/parsing/ft_free.c			\
		srcs/builtins/env.c			\
		srcs/builtins/echo.c			\
		srcs/builtins/cd.c			\
		srcs/builtins/pwd.c			\
		srcs/execution/ft_free_execution.c			\
		srcs/execution/ft_execution.c	\
		srcs/execution/_execute_cmds.c	\
		srcs/execution/in_out_handler.c	\
		srcs/execution/get_next_line/get_next_line.c	\
		srcs/execution/get_next_line/get_next_line_utils.c	\

OBJS = $(SRCS:.c=.o)

INCL =	includes/minishell.h

CC = gcc

RM = rm -f

#FLAGS = -lreadline -Wall -Werror -Wextra -fsanitize=address -g3

FLAGS = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -Wall -Werror -Wextra

%.o.c: $(INCL) Makefile
	$(CC) -c $< -o $@ $(FLAGS)

NAME = minishell

$(NAME): $(OBJS) $(INCL) Makefile
	$(CC) -o $(NAME) $(OBJS) $(FLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: make clean fclean all re