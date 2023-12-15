/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:55:46 by atucci            #+#    #+#             */
/*   Updated: 2023/12/15 15:07:47 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function takes a node and a strings, performs several check 
 * then create the node with the fields initialized if needed, we will go 
 * from there with further implementation
*/

t_list_of_tok	*create_list_of_tok(t_list_of_tok **head, char *spitted_cmd)
{
	t_list_of_tok	*new_node;
	t_list_of_tok	*current;

	new_node = (t_list_of_tok *)malloc(sizeof(t_list_of_tok));
	if (new_node == NULL)
	{
		printf("Error with malloc");
		exit(1);
	}
	new_node->command_as_string = spitted_cmd; // ft_strdup(spitted_cmd);
	new_node->type = type_of_token(spitted_cmd);
	new_node->priority_lev = 0; // for now ok? 
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		new_node->previous = NULL;
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
	// return the tail of the list :)
	return (new_node);
}
