# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 17:43:04 by hrinka            #+#    #+#              #
#    Updated: 2023/12/09 12:33:17 by miyazawa.ka      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ********************** Section for Macros (Variables) ********************** #
# Product file
NAME			= minishell

# Component names
LIBNAME			= libft

# Check the platform
OS				= $(shell uname)

# Enumeration of files
SRC				= main.c \
					builtin_cd.c \
					builtin_cd2.c \
					builtin_echo.c \
					builtin_env.c \
					builtin_exit.c \
					builtin_export.c \
					builtin_pwd.c \
					builtin_unset.c \
					env.c \
					exec_builtin.c \
					exec_child.c \
					executer.c \
					fd.c \
					getpath.c \
					lexer.c \
					lexer_gettoken.c \
					lexer_string.c \
					lexer_string_env.c \
					lexer_string_lst.c \
					lexer_tokenlen.c \
					map_utils.c \
					parser.c \
					parser_cmdnew.c \
					parser_cmdnew_arg.c \
					parser_cmdnew_fdsize.c \
					parser_cmdnew_input.c \
					parser_cmdnew_output.c \
					sighandler.c \
					sigset.c \
					utils.c

# Enumeration of directories
SRCDIR			= ./src
INCDIR			= ./include
LIBDIR			= $(LIBNAME)
OBJDIR			= ./obj

# Macros to replace and/or integrate
SRCS			= $(addprefix $(SRCDIR)/, $(SRC))
OBJS			= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
LIBS			= $(LIBDIR)/$(LIBNAME).a

# Aliases of commands
CC				= cc
RM				= rm

# Command options (flags)
CFLAGS			= -Wall -Wextra -Werror

INCLUDES		= -I$(INCDIR) -I$(LIBDIR)/include
RMFLAGS			= -r

# Dynamic linking to readline
ifeq ($(OS), Darwin)
	INCLUDES	+= -I$(shell brew --prefix readline)/include/
	LDFLAGS 	+= -L$(shell brew --prefix readline)/lib -lreadline
else
	LDFLAGS		+= -lreadline
endif

# ********************* Section for targets and commands ********************* #
# Phonies
.PHONY: all clean fclean re

# Mandatory targets
all: $(LIBS) $(NAME)
clean:
	$(MAKE) clean -C $(LIBDIR)
	-$(RM) $(RMFLAGS) $(OBJDIR)
fclean:
	$(MAKE) fclean -C $(LIBDIR)
	-$(RM) $(RMFLAGS) $(OBJDIR)
	-$(RM) $(RMFLAGS) $(NAME)
re: fclean all

# Recipes
$(NAME): $(OBJS)
	$(CC) $(INCLUDES) $(OBJS) $(LIBS) $(LDFLAGS) -o $(NAME)
$(LIBS):
	$(MAKE) -C $(LIBDIR)
$(OBJDIR):
	@mkdir -p $@
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

# ******** ******** ******** ******** **** ******** ******** ******** ******** #


# Linux OS
# sudo apt install libreadline-dev

# mac OS
# curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
# brew install readline
# brew update && brew upgrade
