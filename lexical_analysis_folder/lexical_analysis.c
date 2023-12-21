/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:14:09 by atucci            #+#    #+#             */
/*   Updated: 2023/12/21 12:17:03 by atucci           ###   ########.fr       */
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
//		free(current->command_as_string);//  DO I NEED TO USE STRDUP (?)
		free(current);
		current = next_node;
	}
	*head = NULL;
}
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
	t_list_of_tok	*token_tail;

	i = 0;
	token_head = NULL;
	if (handling_errors(string) == 1)
	{
		cleaning_input(string); // to shut up the error
		printf("something wrong\n");
		exit(0);
	}
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
		token_tail = create_list_of_tok(&token_head, line_of_commands[i]);
		i++;
	}
	// redirection_wo_spaces(&token_head);
	priority_level(&token_head);
	print_list_tokens(&token_head);
	// call the tree maker function ?
	recursive_tree_builder(&token_head);
	free_list(&token_head);
	free_split(line_of_commands);
	return (0);
}
