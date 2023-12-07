/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:55:46 by atucci            #+#    #+#             */
/*   Updated: 2023/12/07 14:34:41 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function takes a node and a strings, performs several check 
 * then create the node with the fields initialized if needed, we will go 
 * from there with further implementation*/

void	print_list_tokens(t_list_of_tok **head)
{
	t_list_of_tok	*current;
	current = *head;
	while (current != NULL)
	{
	printf("\n|--------------------|\n");
	printf("|ADDS %p |\n", current);// struct s_list_of_tok	*previous;
	printf("|CMD %s\n", current->command_as_string);
	printf("|TYPE \n");//	t_type_of_tok			type;
	printf("|PREV %p \n", current->previous);// struct s_list_of_tok	*previous;
	printf("|NEXT %p \n", current->next); //struct s_list_of_tok	*next;
	printf("|INDEX %d\n", current->index);
	printf("|--------------------|\n\n");
	current = current->next;
	}
}
void	create_list_of_tok(t_list_of_tok **head, char *spitted_cmd)
{
	t_list_of_tok	*new_node;
	t_list_of_tok	*current;

	new_node = (t_list_of_tok *)malloc(sizeof(t_list_of_tok));
	if (new_node == NULL)
	{
		printf("Error with malloc");
		exit(1);
	}
	new_node->command_as_string = ft_strdup(spitted_cmd); // remember to free ?
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		new_node->previous = NULL;
		//new_node->
		new_node->index = 0;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		new_node->previous = current;
		new_node->index = current->index + 1;
	}
//	index++;
//	print_list_tokens(head);
}
