# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atucci <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 09:05:05 by atucci            #+#    #+#              #
#    Updated: 2023/11/08 10:26:57 by atucci           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--------------------------------------------------
# This sets the variable NAME to the name of the executable file that we will build.
NAME = minishell
#--------------------------------------------------
# This sets the variable SRC to a list of C source files that are needed to build the executable.
SRC = minishell.c \
			builtin_folder/built_ins.c \
			lexical_analysis_folder/lexical_analysis.c \
			recursive_parsing_tree/recursive_parsing_tree.c \
			tokenizer_folder/tokenizer.c \
#--------------------------------------------------
# This sets the variable OBJS to a list of object files that need to be built from the SRC files.
OBJS = $(SRC:.c=.o)

#--------------------------------------------------
# This sets the variable HDRS to the path of the header file that is included in the project.
HDRS = $(wildcard *.h) $(wildcard */*.h)

#--------------------------------------------------
# This sets the variable RM to the command that will be used to remove files.
RM = rm -f

#--------------------------------------------------
# This sets the C compiler with specific warning flags.
CC = gcc -Wall -Wextra -Werror

#--------------------------------------------------
# This variable specifies the path to the libft library, which will be used in the project.
LIBFT = libft/libft.a

#--------------------------------------------------
# Color codes for echo commands to make the output more visually informative.
GREEN := \033[1;32m
CYAN := \033[1;36m
YELLOW := \033[1;33m
RED := \033[1;31m
RESET := \033[0m

#--------------------------------------------------
# Rule for compiling C source files into object files.
.c.o:
	${CC} -I ${HDRS} -c $<  ${<:.c=.o}

#--------------------------------------------------
# Rule for building the executable.
$(NAME): $(OBJS)
	@echo "$(GREEN)$(NAME) try to understand how the makefile works! $(RESET)"

#--------------------------------------------------
# Default target: building the executable when running 'make all'.
all: $(NAME)

#--------------------------------------------------
# Rule for cleaning up generated object files.
clean:
	$(MAKE) -C libft clean
	${RM} $(OBJS)
	@echo "$(YELLOW) let's clean up $(RESET)"

#--------------------------------------------------
# Rule for completely removing generated object files and the "fdf" executable.
fclean: clean
	@echo "$(YELLOW)Cleaning up $(NAME) binary...$(RESET)"
	${RM} $(NAME)
	$(MAKE) -C libft fclean

#--------------------------------------------------
# Rule for recompiling the project from scratch.
re: fclean all

#--------------------------------------------------
# .PHONY targets to specify non-file targets.
.PHONY: all clean fclean re
