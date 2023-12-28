/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:37:59 by atucci            #+#    #+#             */
/*   Updated: 2023/12/28 15:20:37 by atucci           ###   ########.fr       */
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
/*
 < : “File Reader”, since it reads input from a file.
*/
int	is_file_reader(char *str)
{
	if (my_strcmp(str, "<") == 0)
		return (1);
	else
		return (0);
}

/* 
 > : “File Writer”, as it writes output to a file.
 */
int	is_file_writer(char *str)
{
	if (my_strcmp(str, ">") == 0)
		return (1);
	else
		return (0);
}

/*
 >> : “File Appender”, because it appends output to a file.
*/
int	is_file_appender(char *str)
{
	if (my_strcmp(str, ">>") == 0)
		return (1);
	else
		return (0);
}

/*
 << : “Inline Input”, as it provides inline input to a command.
*/
int	is_here_doc(char *str)
{
	if (my_strcmp(str, "<<") == 0)
		return (1);
	else
		return (0);
}
