SRCS			=	./groshell.c \
					./builts/cd.c \
					./builts/echo.c \
					./builts/env.c \
					./builts/exit.c \
					./builts/export.c \
					./builts/pwd.c \
					./builts/unset.c \
					./executing/builtsing_fork.c \
					./executing/builtsing_nofork.c \
					./executing/executing.c \
					./executing/execving.c \
					./executing/opening_fds.c \
					./executing/parsing_arg.c \
					./executing/redirecting.c \
					./executing/parsing_arg_new.c \
					./parsing/creating_tkn_cmd.c \
					./parsing/environning.c \
					./parsing/parsing_spliting.c \
					./utils/env_char_to_lst.c \
					./utils/env_lst_to_char.c \
					./utils/freeing.c \
					./utils/libft_plus.c \
					./utils/printing.c \
					./tmp_libft/libft.c \
					./parsing/parsing_lexer/step_one.c \
					./parsing/parsing_lexer/step_one_utils.c \
					./parsing/parsing_cmd/step_two.c \
					./parsing/parsing_cmd/command_validation.c \
					./parsing/expand/expand.c \
					./parsing/expand/expand_utils.c \
					

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