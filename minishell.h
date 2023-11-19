/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:10:19 by atucci            #+#    #+#             */
/*   Updated: 2023/11/19 15:09:04 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "builtin_folder/built_ins.h"
# include "lexical_analysis_folder/lexical_analysis.h"
# include "recursive_parsing_tree/recursive_parsing_tree.h"
# include "tokenizer_folder/tokenizer.h"
# include <unistd.h> // check for the libraris are allowed
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h> // check if this library is allowed
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Define color macros */
# define BLUE    "\033[1;34m"
# define PURPLE  "\033[1;35m"
# define GRAY    "\033[1;30m"
# define GREEN   "\033[1;32m"
# define CYAN    "\033[1;36m"
# define YELLOW  "\033[1;33m"
# define RED     "\033[1;31m"
# define RESET   "\033[0m"
/* Define Background colors macros */
# define BG_RESET        "\033[49m"
# define BG_GREEN        "\033[42m"
# define BG_CYAN         "\033[46m"
# define BG_YELLOW       "\033[43m"
# define BG_RED          "\033[41m"

typedef enum e_tokens
{
	T_WORD,
	T_BAR,
	T_AMP,
	T_SEMI,
	T_GT,
	T_GTGT,
	T_LT,
	T_NL,
	T_EOF,
	T_ERROR
}	t_tokens;

void	token(void);
void	parser(void);
int		lexer(char *string);
void	try_builtin(void);
// function to handle signals
void	handle_ctrl_c(int sig);
void	handle_ctrl_d(void);
void	handle_ctrl_backlash(int sig);

#endif
