/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:10:19 by atucci            #+#    #+#             */
/*   Updated: 2024/01/12 19:25:19 by atucci           ###   ########.fr       */
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
# include <dirent.h>

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

/* Those macro are from a github, they seem
 * more clear to understand when dealing
 * with the pipes, maybe ill use them */

# define READ_END 0
# define WRITE_END 1
/* Those macro are created by me to help me with 
 * the parsing and interpretations of quotes
*/
# define ERROR_QUOTE 0
# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2
# define NO_QUOTE 3
# define SEVERAL_QUOTES 4
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
	T_COMMAND_ARGS,
	T_FILE_NAME
}	t_type_of_tok;

typedef struct s_list_of_tok
{
	t_type_of_tok			type;
	t_type_of_tok			redirect_type;
	int						in_file; // updates
	int						out_file; // updates suggestion github
	char					*file_name;
	char					*token;
	int						index;
	int						priority_lev;
	struct s_list_of_tok	*next;
	struct s_list_of_tok	*previous;
}	t_list_of_tok;


typedef struct s_tree_node
{
	int					fd;
	char				*useful;
	char				*token;
//	t_list_of_tok		*token; // this is a fix (?)
	int					priority_lev;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
	struct s_tree_node	*parent;
}	t_tree_node;

/*lexer part alright*/
int		lexer1(char *param);

/* utils of libft, inside the extra.c */
char	*my_strchr(char *str, int cherry);
int		my_strcmp(const char *str1, const char *str2);
char	*my_strndup(const char *src_str, size_t max_len);
void	print_string_array(char **array);
int		free_string_array(char **array);
/* Advanced utils for builtins or Wildcard */
int		lenght_string_array(char **array);
char	**sort_string_array(char **array);

/* regular expression function */
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
t_list_of_tok	*create_list_of_tok(t_list_of_tok **head, char *spitted_cmd, char **env);
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
// MADE THEM STATIC ALRIGHT
// t_list_of_tok	*node_for_dollar(int level, char *spitted_cmd, char **env);
void	token(void);
void	parser(void);
int		lexer(char *string, char **envp);
void	try_builtin(void);

/* build in functions */
void	minishell_pwd(void);
void	minishell_cd(char *directory);
void	minishell_echo(char *args[]);
void	minishell_export(char *args[]);
void	minishell_env(char **env);
void	minishell_unset(char *variable_name, char *envp[]);
void	minishell_exit(char **args);

void	*which_built_in(t_list_of_tok *node, char **args, char **env);

/* function for the executor */
int		executor(t_list_of_tok **head, char **envp);
char	**find_path_env(char **env);
char	**array_from_list(t_list_of_tok **head);
char	*find_path_command(char *token, char **envp);
void	*execute_command(char *command, char **test, char **envp, t_list_of_tok *current);
int		redirection_process(char *file_name, t_type_of_tok type);
t_list_of_tok	*find_command_in_list(t_list_of_tok **head);

/* fucking redirection are here*/
int		redirect_input(char *file_name);
void	redirect_output(char *file_name, t_type_of_tok type);
void	*here_document(char *delimiter);
void	executor2(void);
void	executor3(void);

/* setting up pipes */
void	set_pipes(t_list_of_tok *first_cmd, t_list_of_tok *secnd_cmd);
void	find_pipes(t_list_of_tok *head);
void	piping_process(t_list_of_tok *cmd_nod);
/**/
// function to handle signals
void	handle_ctrl_c(int sig);
void	handle_ctrl_d(int sig);
void	handle_ctrl_backlash(int sig);
/*function to handle the * wildcards */
int		valid_wildcard(const char *str);
char		**expansion_wildcard(char *wildcard);
#endif
