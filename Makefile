SRCS		=	minishell.c										\
				srcs/utils/utils.c 								\
				srcs/utils/utils_two.c							\
				srcs/utils/utils_three.c						\
				srcs/utils/lst_utils.c 							\
				srcs/utils/lst_utils_env.c 						\
				srcs/utils/env_to_list.c 						\
				srcs/utils/ft_split.c 							\
				srcs/utils/ft_strtrim.c 						\
				srcs/parsing/start_parsing.c 					\
				srcs/parsing/replace_variable.c 				\
				srcs/parsing/impossible_cmd.c 					\
				srcs/parsing/creat_piped_list.c 				\
				srcs/parsing/delete_quotes.c					\
				srcs/parsing/delete_all_space.c					\

OBJS		=	$(SRCS:.c=.o)

CC			=	gcc

RM			=	rm -f

CFLAGS		= 	-Wall -Wextra -Werror -g3

CPPFLAGS	=	-I./includes

NAME		= 	minishell

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY:		all clean fclean re