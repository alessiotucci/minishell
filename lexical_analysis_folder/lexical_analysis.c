/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:14:09 by atucci            #+#    #+#             */
/*   Updated: 2023/12/04 12:37:26 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexical_analysis.h"

int	lexer(char *string)
{
	char **line_of_commands;
	int i = 0;

	line_of_commands = ft_split(string, ' ');
	while (line_of_commands[i])
	{
	if (my_strcmp(line_of_commands[i], "exit") == 0)
		exit(0);
	ft_printf("[%d]\t%s\n", i, line_of_commands[i]);
	i++;
	}
	return (0);
}
