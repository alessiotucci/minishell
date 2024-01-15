/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_order_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 19:21:22 by atucci            #+#    #+#             */
/*   Updated: 2024/01/15 16:45:49 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*2)  Helper function to create a new node */
t_list_of_tok	*create_empty_node(void)
{
	t_list_of_tok	*new_node;

	new_node = (t_list_of_tok *)malloc(sizeof(t_list_of_tok));
	if (new_node == NULL)
	{
		printf("Error with malloc");
		exit(1);
	}
	new_node->token = "EMPTY";
	new_node->type = T_BUILTIN;
	new_node->priority_lev = 0;
	new_node->next = NULL;
	new_node->previous = NULL;
	new_node->index = -1;
	new_node->file_name = NULL;
	new_node->in_file = STDIN_FILENO;
	new_node->out_file = STDOUT_FILENO; // this is the latest updated here
	return (new_node);
}

/* Check if the previous node is valid */
int	is_valid_prev(t_list_of_tok *prev)
{
	if (prev == NULL || (prev->type != T_COMMAND && prev->type != T_FLAG && prev->type != T_COMMAND_ARGS))
		return (0);
	else
		return (1);
}

/* Check if the next node is valid */
int	is_valid_next(t_list_of_tok *next)
{
	if (next == NULL || (next->type != T_COMMAND && next->type != T_FLAG && next->type != T_COMMAND_ARGS))
		return (0);
	else
		return (1);
}

/* Check if the next node is a command or built-in */
int	is_command_or_builtin(t_list_of_tok *next)
{
	if (next == NULL || next->type != T_COMMAND || next->type != T_BUILTIN)
		return (0);
	else
		return (1);
}

void	find_empty_redirection(t_list_of_tok **head)
{
	t_list_of_tok	*current;
	t_list_of_tok	*prev;
	t_list_of_tok	*next;// bingAi

	//prev = NULL;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		prev = current->previous;
		// Check if the current node is a redirection
		if (current->type == T_REDIR_OUT || current->type == T_REDIR_IN || current->type == T_REDIR_APP)
		{
			if (current != NULL && prev != NULL && next != NULL)
			printf("current: (%s) has before (%s) and after (%s)\n", current->token, prev->token, next->token);
			// Check if the previous node is not a command, flag, or command argument
			// or if the next node is not a command, flag, or command argument
			printf("\n\t[Performing check on prev and next]\n");
			if (is_valid_prev(prev) == 0 || is_valid_next(next) == 0 || is_command_or_builtin(next) == 0)
			{
				// Create an "EMPTY" node and insert it before the current node
				printf("the code would insert a empty node\n");
				//print_node(current);
				/*
				t_list_of_tok *empty_node = create_empty_node();
				empty_node->next = current;
				empty_node->previous = prev;
				if (prev != NULL)
					prev->next = empty_node;
				else
					// Update the head of the list if necessary
					*head = empty_node;
				current->previous = empty_node;
				// Update the previous node to be the "EMPTY" node
				prev = empty_node;
				*/
			}
			else
				prev = current;
		}
		else
			prev = current;
		current = current->next;
	}
}
t_list_of_tok	**update_list_order(t_list_of_tok **head)
{
	find_empty_redirection(head);
	return (head);
}
