/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:14:09 by atucci            #+#    #+#             */
/*   Updated: 2023/12/07 14:34:58 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lexer(char *string)
{
	char **line_of_commands;
	int i = 0;
	t_list_of_tok	*token_head;

	token_head = NULL;
	line_of_commands = ft_split(string, ' ');
	while (line_of_commands[i])
	{
	if (my_strcmp(line_of_commands[i], "exit") == 0)
		exit(0);
	// create a node of the list?
	// create a function that takes the node, the commands[i], and create the list.
	create_list_of_tok(&token_head, line_of_commands[i]);
	i++;
	}
	// a nice function that prints the list of tokens? 
	print_list_tokens(&token_head);
	return (0);
}
