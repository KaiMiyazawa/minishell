# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 18:29:50 by miyazawa.ka       #+#    #+#              #
#    Updated: 2023/11/29 21:53:57 by miyazawa.ka      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Makefile
NAME		=	minishell
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
RM		=	rm -rf

BUILTINS = ms_builtin_echo \
			ms_builtin_env \
			ms_builtin_exit \
			ms_builtin_export \
			ms_builtin_pwd \
			ms_builtin_unset \
			ms_builtin_cd
DEBUG = debug_funcs
EXECUTER = executer ms_fd ms_exec_child
FREE = free
LEXER = lexer tk_list tk_utils expander
MAIN = main make_path minishell
PARSER = parser ms_parser_cmdnew_arg ms_getpath
SIGNAL = signal

#FILES AND PATH
HEADER_SRCS	=	minishell.h
HEADER_DIR	=	include/
HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_SRCS))

#SRC
SRC	=	$(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
		$(addsuffix .c, $(addprefix srcs/DEBUG/, $(DEBUG))) \
		$(addsuffix .c, $(addprefix srcs/executer/, $(EXECUTER))) \
		$(addsuffix .c, $(addprefix srcs/free/, $(FREE))) \
		$(addsuffix .c, $(addprefix srcs/lexer/, $(LEXER))) \
		$(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
		$(addsuffix .c, $(addprefix srcs/parser/, $(PARSER))) \
		$(addsuffix .c, $(addprefix srcs/signal/, $(SIGNAL))) \

OBJ	=	$(SRC:.c=.o)

 #LIBFT PATH
LIBFT_DIR	=	./libft
LIBFT		=	./libft/libft.a

 #READLINE PATH
RL_HEADER	=	$(shell brew --prefix readline)/include
RL_LIB		=	$(shell brew --prefix readline)/lib

#COMMANDS
.c.o: $(HEADER)
	@printf "$(DEFAULT)-m $(SKY)Generating minishell objects... %-33.33s\r$(DEFAULT)" $@
	@${CC} ${FLAGS} -o $@ -c $<  -I$(RL_HEADER)

$(NAME):		$(OBJ)
				@echo "\n"
				@chmod 755 put_a_endless
				@make fclean -C $(LIBFT_DIR)
				@make bonus -C $(LIBFT_DIR)
				@$(CC) ${FLAGS} $(OBJ) $(LIBFT) -o $(NAME) -L$(RL_LIB) -lreadline
				@echo -m "$(GREEN)$(NAME) created!$(DEFAULT)"

all:			$(NAME)

clean:
				@$(RM) $(OBJ)
				@echo -m "$(YELLOW)minishell object files deleted!\n$(DEFAULT)"

fclean:			clean
				@$(RM) $(NAME)
				@echo -m "$(RED)minishell all deleted!\n$(DEFAULT)"

re:				fclean all

j:				re
				@$(RM) $(OBJ)
				@echo -m "$(YELLOW)minishell object files deleted!\n$(DEFAULT)"

.PHONY:		all clean fclean bonus re j

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
SKY = \033[1;36m
DEFAULT = \033[0m
