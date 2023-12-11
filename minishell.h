/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:10:19 by atucci            #+#    #+#             */
/*   Updated: 2023/12/11 13:26:00 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "builtin_folder/built_ins.h"
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


typedef enum e_type_of_tok
{
	T_COMMAND,
	T_FLAG,
	T_BUILTIN,
	T_DOLLAR, // $
	T_PIPES, // | 
	T_REDIR_IN, // >
	T_REDIR_OUT, // <
	T_REDIR_APP, // >>
	T_REDIR_DELIMER, // << 
	T_LOGIC_OPERAR // && or || 
}	t_type_of_tok;

typedef struct s_list_of_tok
{
	char					*command_as_string;
	t_type_of_tok			type;
	struct s_list_of_tok	*next;
	struct s_list_of_tok	*previous;
	int						index;
}	t_list_of_tok;

/*lexer part alright*/
int		lexer1(char *param);
int		my_strcmp(const char *str1, const char *str2);
int		is_file_reader(char *str);
int		is_file_writer(char *str);
int		is_file_appender(char *str);
int		is_delimiter(char *str);
int		is_pipe(char *str);
int		is_logical_op(char *str);
int		is_dollar(char *str);
int		is_builtin(char *str);
/*Starting working on the parsing*/
void			create_list_of_tok(t_list_of_tok **head, char *spitted_cmd);
void			print_list_tokens(t_list_of_tok **head);
//void			type_of_token(char *spitted);

// pork around
char	*replace_me(char *str, char quote, char replacement, char me);
char	*add_spaces_around_parentheses(char *command);

 t_type_of_tok	type_of_token(char *spitted);

void	token(void);
void	parser(void);
int		lexer(char *string);
void	try_builtin(void);
// function to handle signals
void	handle_ctrl_c(int sig);
void	handle_ctrl_d(int sig);
void	handle_ctrl_backlash(int sig);

#endif
