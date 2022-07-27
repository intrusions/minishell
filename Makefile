SRCS			=	./groshell.c \
					./executing/builts/cd.c \
					./executing/builts/echo.c \
					./executing/builts/env.c \
					./executing/builts/exit.c \
					./executing/builts/export.c \
					./executing/builts/export_utils.c \
					./executing/builts/pwd.c \
					./executing/builts/unset.c \
					./executing/builtsing_fork.c \
					./executing/builtsing_nofork.c \
					./executing/executing.c \
					./executing/execving.c \
					./executing/opening_fds.c \
					./executing/parsing_arg.c \
					./executing/redirecting.c \
					./executing/redirecting_utils.c \
					./executing/parsing_arg_new.c \
					./parsing/parser/parsing_spliting.c \
					./utils/env_char_to_lst.c \
					./utils/env_char_to_lst_utils.c \
					./utils/env_lst_to_char.c \
					./utils/freeing.c \
					./utils/ft_split.c \
					./utils/utils_one.c \
					./utils/utils_two.c \
					./utils/utils_three.c \
					./utils/utils_four.c \
					./parsing/lexer/lexer.c \
					./parsing/lexer/lexer_utils.c \
					./parsing/lexer/lexer_utils_two.c \
					./parsing/parser/parser.c \
					./parsing/parser/parser_utils.c \
					./parsing/expander/expand.c \
					./parsing/expander/expand_utils.c \
					

OBJS			= 	$(SRCS:.c=.o)

CC				= 	gcc

RM				= 	rm -f

CFLAGS			= 	-Wall -Wextra -Werror

NAME			= 	minishell

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME) $(TH_FLAGS)

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY:		all clean fclean re