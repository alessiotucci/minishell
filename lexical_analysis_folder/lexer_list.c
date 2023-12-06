/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:55:46 by atucci            #+#    #+#             */
/*   Updated: 2023/12/06 10:05:55 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexical_analysis.h"

/*This function takes a node and a strings, performs several check 
 * then create the node with the fields initialized if needed, we will go 
 * from there with further implementation*/

void	create_list_of_tok(t_list **head, char *spitted_cmd)
{
	t_list	*new_node;
	t_list	*current;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
	{
		printf("Error with malloc");
		exit(1);
	}
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	printf("new node with line %s\n", spitted_cmd);
}
