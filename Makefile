 #SETUP
NAME		=	minishell
CC			=	gcc
#開発段階でいちいちwarningをerror扱いされるとめんどくさいケースがあると思うので、一時的に -Werror を外せるように、コメントでもう一つのフラッグを書いています。
#FLAGS		=	-Wall -Wextra -Werror
FLAGS		=	-Wall -Wextra
RM		=	rm -rf

#FILES AND PATH
HEADER_SRCS	=	minishell.h
HEADER_DIR	=	include/
HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_SRCS))

MPATH_SRCS	=	error.c\
			evaluater.c \
			lexer.c\
			main.c\
			minishell.c \
			perser.c\
			utils_libft.c
MPATH_DIR	=	mandatory/
MPATH		=	$(addprefix $(MPATH_DIR), $(MPATH_SRCS))
OBJ_M		=	$(MPATH:.c=.o)

 #READLINE PATH
RL_HEADER	=	$(shell brew --prefix readline)/include
RL_LIB		=	$(shell brew --prefix readline)/lib

#COMMANDS
%.o: %.c $(HEADER) Makefile
				@${CC} ${FLAGS} -I$(RL_HEADER) -c $< -o $@

$(NAME):		$(OBJ_M)
				@$(CC) ${FLAGS} $(OBJ_M) -o $(NAME) -L$(RL_LIB) -lreadline
				@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

all:			$(NAME)

clean:
				@$(RM) $(OBJ_M)
				@$(RM) $(OBJ_B)
				@echo -e "$(YELLOW)object files deleted!$(DEFAULT)"

fclean:			clean
				@$(RM) $(NAME)
				@echo -e "$(RED)all deleted!$(DEFAULT)"

re:				fclean all

.PHONY:		all clean fclean bonus re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
