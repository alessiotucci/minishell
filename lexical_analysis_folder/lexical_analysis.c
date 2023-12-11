/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:14:09 by atucci            #+#    #+#             */
/*   Updated: 2023/12/11 09:44:13 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**/

/*The main function of the lexer, we use split and get the command line*/
int	lexer(char *string)
{
	char **line_of_commands;
	int i = 0;
	t_list_of_tok	*token_head;
	char *new_string;

	token_head = NULL;
	// add spaces before parethensis
	// scan for " " or ' ' 
	new_string = replace_me(string, '"', '\t', ' ');
	printf("%s\n", new_string);
	if (new_string != NULL) // check for null
	new_string = replace_me(string, 39, '\t', ' ');
	printf("%s\n", new_string);
	if (new_string == NULL)
		return (1); // check for null
	new_string = add_spaces_around_parentheses(string);
	line_of_commands = ft_split(new_string, ' ');
	while (line_of_commands[i])
	{
	line_of_commands[i] = replace_me(line_of_commands[i], '"', ' ', '\t');
	line_of_commands[i] = replace_me(line_of_commands[i], 39, ' ', '\t');
	if (my_strcmp(line_of_commands[i], "exit") == 0)
		exit(0);
	create_list_of_tok(&token_head, line_of_commands[i]);
	i++;
	}
	// after creating the list, I need to analyze each single node of the list?
	// a nice function that prints the list of tokens? 
	print_list_tokens(&token_head);
	return (0);
}
