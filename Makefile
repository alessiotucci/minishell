# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atucci <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 09:05:05 by atucci            #+#    #+#              #
#    Updated: 2023/11/07 15:37:39 by atucci           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--------------------------------------------------
# This sets the variable NAME to the name of the executable file that we will build.
NAME = minishell
#--------------------------------------------------
# This sets the variable SRC to a list of C source files that are needed to build the executable.
SRC = ./path_to_your_source_files.c

#--------------------------------------------------
# This sets the variable OBJS to a list of object files that need to be built from the SRC files.
OBJS = $(SRC:.c=.o)

#--------------------------------------------------
# This sets the variable HDRS to the path of the header file that is included in the project.
HDRS = ./path_to_your_header_files.h

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
	${CC} -I ${HDRS} -c $< -o ${<:.c=.o}

#--------------------------------------------------
# Rule for building the executable.
$(NAME): $(OBJS)
	@echo "$(GREEN)$(MIC_DROP_EMOJI)$(NAME) binary created successfully! $(MIC_DROP_EMOJI)$(RESET)"

#--------------------------------------------------
# Default target: building the executable when running 'make all'.
all: $(NAME)

#--------------------------------------------------
# Rule for cleaning up generated object files.
clean:

