/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:14:09 by atucci            #+#    #+#             */
/*   Updated: 2023/12/11 10:23:08 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/**/
static int	handling_errors(char *input)
{
	int	count_single;
	int	count_double;
	int	i;

	i = 0;
	count_double = 0;
	count_single = 0;
	while (input[i])
	{
		if (input[i] == '"' )
			count_double++;
		if (input[i] == 39)
			count_single++;
		i++;
	}
	if (count_single % 2 == 0 && count_double % 2 == 0)
		return (0);
	else
		return (1);
}

/*Static function to perform some cleaning in the input*/
static void	cleaning_input(char *input)
{
	char	*cleaned;

	cleaned = replace_me(input, '"', '\t', ' ');
}

/*The main function of the lexer, we use split and get the command line*/
int	lexer(char *string)
{
	char			**line_of_commands;
	int				i;
	t_list_of_tok	*token_head;
	char			*new_string;

	i = 0;
	token_head = NULL;
	if (handling_errors(string) == 1)
	{
		cleaning_input(string); // to shut up the error
		printf("something wrong\n");
		exit(0);
	}
	new_string = replace_me(string, '"', '\t', ' ');
	new_string = replace_me(string, 39, '\t', ' ');
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
	print_list_tokens(&token_head);
	return (0);
}
