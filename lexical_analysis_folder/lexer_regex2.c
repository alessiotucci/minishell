/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_regex2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:37:59 by atucci            #+#    #+#             */
/*   Updated: 2024/01/01 15:58:43 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_pipe(char *str)
{
	if (my_strcmp(str, "|") == 0)
		return (1);
	else
		return (0);
}

int	is_parent(char *str)
{
	if (my_strcmp(str, "(") == 0 || my_strcmp(str, ")") == 0)
		return (1);
	else
		return (0);
}

int	is_flag(char *str)
{
	if (str[0] == '-')
		return (1);
	else
		return (0);
}

int	is_dollar(char *str)
{
	if (str[0] == '$')
		return (1);
	else
		return (0);
}
