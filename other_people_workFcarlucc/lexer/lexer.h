/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:19:08 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/11/11 17:18:06 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define START 0
# define ADD 1
# define LIST 2
# define GET 3

# include "../minishell.h"

char			*handle_quotes(char *str, char *res, int *i, int *j);
char			*handle_two(char *str, char *res, int *i, int *j);
char			*handle_one(char *str, char *res, int *i, int *j);
int				count_syntax(char *str);
char			*fix_white_spaces(char *str);
char			*fix_syntax(char *str);
// struct s_list	*start_back(struct s_list *here_doc_lst);
// struct s_list	*get_here_doc(struct s_list **here_doc_lst);
// void			handle_here_doc_sig(int signum);
// void			*handle_list_heredocs(int op);
// void			handle_here_doc(char *del, t_mini *mini);
// char			*create_del(char *s);
void			del(void *str);
int				check(char *s);
int				checks(char *s, int *i);
int				check_parentheses(char *s, int *i);
int				check_number(char *s);
int				check_quote(char *s);
int				check_operator(char *s, int *i);
int				counter(int count);
int				is_op(char *c);
int				is_red(char *c);
int				is_op_or_red(char *s, int *i);
int				is_one_char(char *c);
int				is_two_char(char *c);

int				is_double(char *s, int *i);
#endif
