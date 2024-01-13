/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:14:09 by atucci            #+#    #+#             */
/*   Updated: 2024/01/13 20:24:29 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



static void	free_list(t_list_of_tok **head)
{
	t_list_of_tok *current;
	t_list_of_tok *next_node;

	current = *head;
	while (current != NULL)
	{
		next_node = current->next;
//		free(current->token);//  DO I NEED TO USE STRDUP (?)
		free(current);
		current = next_node;
	}
	*head = NULL;
}
/* Handling the quotes 
int	handling_quotes(char *input)
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
	if (count_single == 0 && count_double == 0)
		return (NO_QUOTE);
	else if (count_single != 0 && count_double == 0)
		return (SINGLE_QUOTE);
	else if (count_single == 0 && count_double != 0)
		return (DOUBLE_QUOTE);
	else
		return (ERROR_QUOTE);
} */

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
		return (printf("Not interpret unclosed quotes\n"));
	return (0);
}

/* Function to check parentheses
 * it returns ZERO in ok case*/
int	first_check_parent(char *string)
{
	if (check_parentheses(string))
		return (ft_printf("syntax error near unexpected token\n"));
	return (0);
}
/* Function to replace characters in string */
char	*replace_chars(char *string)
{
	char	*new_string;

	new_string = replace_me(string, '"', '\t', ' ');
	new_string = replace_me(string, 39, '\t', ' ');
	new_string = add_spaces_around_symbols(string);
	return (new_string);
}

/* Function to create list of tokens */
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
//		printf("flag: %d\n", flag);
		create_list_of_tok(token_head, line_of_commands[i], env, flag);
		i++;
	}
}
/*The main function of the lexer, we use split and get the command line*/
int	lexer(char *string, char **env)
{
	char			**line_of_commands;
	int				i;
	t_list_of_tok	*token_head;
	char			*new_string;

	i = 0;
	token_head = NULL;
	if (handle_quotes(string) || first_check_parent(string))
		return (1);
	new_string = replace_chars(string);
	line_of_commands = ft_split(new_string, ' ');
	create_tokens(line_of_commands, &token_head, env);
	//priority_level(&token_head);
	update_token_types(&token_head);
	//print_list_tokens(&token_head);
	executor(&token_head, env);
	free_list(&token_head);
	free_string_array(line_of_commands);
	return (0);
}
