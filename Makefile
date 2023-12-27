# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atucci <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 09:05:05 by atucci            #+#    #+#              #
#    Updated: 2023/12/27 09:37:15 by atucci           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------
# Setting the variable name to the name of the executable file
NAME = minishell


#this was supposed to be the line to make everything	# $(wildcard *.c) $(wildcard */*.c)
#------------------------------------------------------------------------------
# Declaring all the sources file needed to build the "philo" executable
SRC = ./minishell.c \
	./signals.c \
	./builtin_folder/built_ins.c \
	./builtin_folder/builtin_helper.c \
	./lexical_analysis_folder/lexical_analysis.c \
	./lexical_analysis_folder/lexer_helper.c \
	./lexical_analysis_folder/lexer_list.c \
	./lexical_analysis_folder/lexer_token.c \
	./lexical_analysis_folder/helping_helper.c \
	./lexical_analysis_folder/parethesis.c \
	./executor_folder/utils.c \
	./executor_folder/executor.c \
	./executor_folder/exec_helper.c \
	./executor_folder/exec_files.c \
	./recursive_parsing_tree/recursive_parsing_tree.c \
	./recursive_parsing_tree/tree_helper.c \
	./printf_for_debug/debug.c # this is just for debugging

#------------------------------------------------------------------------------
# Setting the variables object to a list of object neede to build from the src
OBJS = $(SRC:.c=.o)


#------------------------------------------------------------------------------
# Setting the variable header to the path of the header file 
HDRS = ./minishell.h $(wildcard */*.h)

#--------------------------------------------------
# This variable specifies the path to the libft library, which will be used in the project.
LIBFT = libft/libft.a

#------------------------------------------------------------------------------
# Setting the var RM to remove them files
RM = rm -f


#------------------------------------------------------------------------------
# This set the C compiler with the specific warning flags
CC = gcc -Wall -Werror -Wextra

# Color codes for echo commands to make the output more visually informative.
GREEN := \033[1;32m
CYAN := \033[1;36m
YELLOW := \033[1;33m
RED := \033[1;31m
RESET := \033[0m

#--------------------------------------------------
# Rule for building the "minishell" executable.
$(NAME): $(OBJS)
	@echo "$(CYAN)Building $(NAME)...$(RESET)"
	$(MAKE) -C libft
	${CC} -o $(NAME) $(OBJS) $(LIBFT) -lreadline
	@echo "$(GREEN) $(NAME)minishell  created successfully! $(RESET)"

#--------------------------------------------------
# Default target: building the "philo" executable when running 'make all'.
all: $(NAME)

#--------------------------------------------------
# Rule for cleaning up generated object files.
clean:
	@echo "$(YELLOW)Cleaning up object files...$(RESET)"
	${RM} $(OBJS)

#--------------------------------------------------
# Rule for completely removing generated object files and the "philo" executable.
fclean: clean
	@echo "$(YELLOW)Cleaning up $(NAME) executalbe binary...$(RESET)"
	${RM} $(NAME)

#--------------------------------------------------
# Rule for recompiling the project from scratch.
re: fclean all

#--------------------------------------------------
# .PHONY targets to specify non-file targets.
.PHONY: all clean fclean re


#--------------------------------------------------
# Rule for deleting the hidden files generated
hidden:
	@echo "$(YELLOW) Listing hidden files:"
	@find . \( -name ".DS_Store" -o -name ".*.swp" -o -name ".*.swo" -o -name "a.out" \) -type f -print
	@echo "$(RESET)$(RED) Deleting hidden files: $(RESET)"
	@find . \( -name ".DS_Store" -o -name ".*.swp" -o -name ".*.swo" -o -name "a.out" \) -type f -delete

