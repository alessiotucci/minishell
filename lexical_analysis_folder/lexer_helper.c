/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:37:59 by atucci            #+#    #+#             */
/*   Updated: 2023/12/08 19:46:02 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_strcmp(const char *str1, const char *str2)
{
	size_t	count;

	count = 0;
	while (str1[count] != '\0'|| str2[count] != '\0')
	{
		if (str1[count] > str2[count])
			return (1);
		else if (str1[count] < str2[count])
			return (-1);
		count++;
	}
	return (0);
}
int	is_pipe(char *str)
{
	if(my_strcmp(str, "|") == 0)
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
int	is_inline_input(char *str)
{
	if (my_strcmp(str, "<<") == 0)
		return (1);
	else
		return (0);
}

