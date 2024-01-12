/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:14:09 by atucci            #+#    #+#             */
/*   Updated: 2024/01/12 19:24:53 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	free_split(char **tab)
{
	int	count;

	count = 0;
	while (tab[count])
	{
		free(tab[count]);
		count++;
	}
	free(tab);
	return (0);
}

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

/*Static function to perform some cleaning in the input*/
void	cleaning_input(char *input)
{
	char	*cleaned;

	cleaned = replace_me(input, '"', '\t', ' ');
	printf("%s\n", cleaned);
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
	if (handling_quotes(string) == ERROR_QUOTE)
		return (printf("Not interpret unclosed quotes\n"));
	if (check_parentheses(string))
		return (ft_printf("bad parentheses\n"));
	new_string = replace_me(string, '"', '\t', ' ');
	new_string = replace_me(string, 39, '\t', ' ');
	new_string = add_spaces_around_symbols(string);
	line_of_commands = ft_split(new_string, ' ');
	while (line_of_commands[i]) // I need to perform additional_check here?
	{
		line_of_commands[i] = replace_me(line_of_commands[i], '"', ' ', '\t');
		line_of_commands[i] = replace_me(line_of_commands[i], 39, ' ', '\t');
		create_list_of_tok(&token_head, line_of_commands[i], env);
		i++;
	}
	priority_level(&token_head);
	update_token_types(&token_head);
	//return (print_list_tokens(&token_head), 1);
	executor(&token_head, env);
	free_list(&token_head);
	free_split(line_of_commands);
	return (0);
}
