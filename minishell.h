/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:10:19 by atucci            #+#    #+#             */
/*   Updated: 2023/11/09 14:45:36 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "libft/libft.h"
# include "builtin_folder/built_ins.h"
# include "lexical_analysis_folder/lexical_analysis.h"
# include "recursive_parsing_tree/recursive_parsing_tree.h"
# include "tokenizer_folder/tokenizer.h"

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
void	lexer(void);
void	try_builtin(void);

#endif
