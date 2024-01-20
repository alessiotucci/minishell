/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:14:09 by atucci            #+#    #+#             */
/*   Updated: 2024/01/20 23:26:27 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int	handling_quotes(char *input)
{
	int	count_single;
	int	count_double;
	int	i;
	int	total_quotes;

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
	total_quotes = count_single + count_double;
	if (total_quotes % 2 != 0)
		return (ERROR_QUOTE);
	else if (total_quotes > 2)
		return (SEVERAL_QUOTES);
	else if (count_single == 0 && count_double == 0)
		return (NO_QUOTE);
	else if (count_single != 0 && count_double == 0)
		return (SINGLE_QUOTE);
	else if (count_single == 0 && count_double != 0)
		return (DOUBLE_QUOTE);
	else
		return (NO_QUOTE);
}

/* Function to handle quotes 
 * it returns ZERO in ok case*/
int	handle_quotes(char *string)
{
	if (handling_quotes(string) == ERROR_QUOTE)
		return (set_g_exit(GENERAL_ERROR), printf("Not interpret unclosed quotes\n"));
	return (0);
}

/* Function to check parentheses
 * it returns ZERO in ok case*/
int	first_check_parent(char *string)
{
	if (check_parentheses(string))
		return (set_g_exit(GENERAL_ERROR), printf("syntax error near unexpected token\n"));
	return (0);
}

/*2 Function to create list of tokens */
void	create_tokens(char **line_of_commands, t_list_of_tok **token_head, char **env)
{
	int	i;
	int	flag;

	i = 0;
	while (line_of_commands[i])
	{
		line_of_commands[i] = replace_me(line_of_commands[i], '"', ' ', '\t');
		line_of_commands[i] = replace_me(line_of_commands[i], 39, ' ', '\t');
		flag = handling_quotes(line_of_commands[i]);
		create_list_of_tok(token_head, line_of_commands[i], env, flag);
		i++;
	}
}

/*1 The main function of the lexer, we use split and get the command line*/
int	lexer(char *string, char **env)
{
	char			**line_of_commands;
	t_list_of_tok	*token_head;
	char			*new_string;

	token_head = NULL;
	if (handle_quotes(string) || first_check_parent(string))
		return (1);
	new_string = replace_chars(string);
	line_of_commands = ft_split(new_string, ' ');
	create_tokens(line_of_commands, &token_head, env);
	priority_level(&token_head);
	update_token_types(&token_head);
//	printf("do you want to perfomr some check here!\n");
	//print_list_tokens(&token_head);
	update_list_order(&token_head);
//	printf("\n***\t\nafter the change\n");
//	print_list_tokens(&token_head);
//	print_list_tokeny(&token_head);
//	return (1);
	executor(&token_head, env);
	free_list(&token_head);
//	free_string_array(line_of_commands);
	return (0);
}
