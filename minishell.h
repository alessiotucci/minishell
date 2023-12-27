/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:10:19 by atucci            #+#    #+#             */
/*   Updated: 2023/12/27 11:28:37 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "builtin_folder/built_ins.h"
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
/* Define the flag for open redirection*/
#define OVERWRITE_FLAGS (O_WRONLY | O_CREAT | O_TRUNC)
#define APPEND_FLAGS (O_WRONLY | O_CREAT | O_APPEND)



typedef enum e_type_of_tok
{
	T_COMMAND,
	T_FLAG,
	T_BUILTIN,
	T_PARENT, // ( OR )
	T_DOLLAR, // $
	T_PIPES, // | 
	T_REDIR_IN, // >
	T_REDIR_OUT, // <
	T_REDIR_APP, // >>
	T_HERE_DOC, // << 
	T_LOGIC_OPERAR,// && or || 
	T_COMMAND_ARGS
}	t_type_of_tok;

typedef struct s_list_of_tok
{
	int						fd_redirect;
	char					*file_name;
	char					*command_as_string;
	t_type_of_tok			type;
	struct s_list_of_tok	*next;
	struct s_list_of_tok	*previous;
	int						index;
	int						priority_lev;
}	t_list_of_tok;


typedef struct s_tree_node
{
	int					fd;
	char				*useful;
	char				*command_as_string;
	t_list_of_tok		*token; // this is a fix (?)
	int					priority_lev;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
	struct s_tree_node	*parent;
}	t_tree_node;




/*lexer part alright*/
int		lexer1(char *param);
int		my_strcmp(const char *str1, const char *str2);
int		is_file_reader(char *str);
int		is_file_writer(char *str);
int		is_file_appender(char *str);
int		is_here_doc(char *str);
int		is_pipe(char *str);
int		is_logical_op(char *str);
int		is_dollar(char *str);
int		is_flag(char *str);
int		is_builtin(char *str);
int		is_parent(char *str);
/*Starting working on the parsing*/
t_list_of_tok	*create_list_of_tok(t_list_of_tok **head, char *spitted_cmd);
void			print_list_tokens(t_list_of_tok **head);
void			print_node(t_list_of_tok *node);
//void			type_of_token(char *spitted);

void	update_token_types(t_list_of_tok **head);
// pork around
char	*replace_me(char *str, char quote, char replacement, char me);
char	*add_spaces_around_symbols(char *command);
// fucking parentheses
int	check_parentheses(char* str);

// level of priority
void	priority_level(t_list_of_tok **head);

// function for the tree it seems 
t_list_of_tok	**recursive_tree_builder(t_list_of_tok **head);
void	parser(void);
int		print_tree(t_tree_node *root, int level);
void	tree_maker2(void);
void	tree_maker3(void);
// yet an other function 
t_type_of_tok	type_of_token(char *spitted);

t_list_of_tok	*create_node(int level, char *spitted_cmd);

void	token(void);
void	parser(void);
int		lexer(char *string, char **envp);
void	try_builtin(void);
/* function for the executor */

void	executor(t_list_of_tok **head, char **envp);
char	**find_path_env(char **env);
char	**argv_for_exceve(t_list_of_tok **head);

/* fucking redirection are here*/
void	redirect_input(char *file_name);
void	redirect_output(t_list_of_tok *current, t_type_of_tok type);
void	executor2(void);
void	executor3(void);

/**/
// function to handle signals
void	handle_ctrl_c(int sig);
void	handle_ctrl_d(int sig);
void	handle_ctrl_backlash(int sig);

#endif
