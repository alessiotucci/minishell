/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:10:16 by atucci            #+#    #+#             */
/*   Updated: 2023/12/06 09:37:59 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		lexer1(char *param);
int		my_strcmp(const char *str1, const char *str2);
int	is_double_char_operator(char *str);
int	is_single_char_operator(char *str);
int	is_redirection(char *str);
int	is_operation(char *str);

/*Starting working on the parsing*/
void	create_list_of_tok();
