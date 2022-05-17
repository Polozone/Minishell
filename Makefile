SRCS =	srcs/main.c				\
		srcs/split.c			\
		srcs/Path_list_maker.c	\
		srcs/strings_manip.c	\
		srcs/printing_ft.c		\
		srcs/quote.c			\
		srcs/syntax_error.c		\
		srcs/builtin_check.c	\
		srcs/parsing.c		

OBJS = $(SRCS:.c=.o)

INCL =	includes/minishell.h

CC = gcc

RM = rm -f

FLAGS = -Wall -Werror -Wextra -lreadline

%.o.c: $(INCL) Makefile
	$(CC) $(FLAGS) -c $< -o $@

NAME = minishell

$(NAME): $(OBJS) $(INCL) Makefile
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: make clean fclean all re