/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_order_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 19:21:22 by atucci            #+#    #+#             */
/*   Updated: 2024/01/18 11:55:37 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_a_redirection(t_list_of_tok *token);

/*2)  Helper function to create a new node */
t_list_of_tok	*create_empty_node(void)
{
	t_list_of_tok	*new_node;

	new_node = (t_list_of_tok *)malloc(sizeof(t_list_of_tok));
	if (new_node == NULL)
		return(printf("Error with malloc"), NULL);
	new_node->token = "EMPTY";
	new_node->type = T_BUILTIN;
	new_node->priority_lev = 0;
	new_node->next = NULL;
	new_node->previous = NULL;
	new_node->index = -1; // this is the only change made here
	new_node->file_name = NULL;
	new_node->in_file = STDIN_FILENO;
	new_node->out_file = STDOUT_FILENO;
	return (new_node);
}

/* Check if the previous node is valid */
int	is_valid_prev(t_list_of_tok *node)
{
	if (node == NULL || (node->type != T_BUILTIN && node->type != T_COMMAND && node->type != T_FLAG && node->type != T_COMMAND_ARGS))
	//	return (printf("\tprev is NULL, or different than COMMAND\n"), 0);
	return (0);
	else
	//	return (printf("\tprev is not null, or it's command or builtins\n"), 1);
	return (1);
}

/* Check if the next node is valid */
int	is_valid_next(t_list_of_tok *node)
{
	if (node == NULL || (node->type != T_COMMAND && node->type != T_FLAG && node->type != T_COMMAND_ARGS))
		return (0);
	else
		return (1);
}

/* Check if the next node is a command, built-in, or followed by a command/built-in */
int	is_command_or_builtin(t_list_of_tok *node)
{
	// Print the token of the next node for debugging purposes
	/*
	if (node != NULL)
		printf("\nNEXT is: %s\n", node->token);
	else
		printf("\nNEXT is: NULL\n");
	*/
	if (node == NULL || (node->type != T_COMMAND && node->type != T_BUILTIN && node->type != T_FILE_NAME))
	//	return (printf("next is null or not a command/built-in, not a filename\n"), 0);
	return (0);
	else if (node->type == T_FILE_NAME && (node->next->type == T_COMMAND || node->next->type == T_BUILTIN || is_a_redirection(node->next)))
	//	return (printf("\tafter file_name there is a command/built-in, or a redirection!!!\n"), 2);
	return (2);
	else
	//	return (printf("\tnext is a command/built-in\n"), 1);
	return (1);
}
/* Determine what follows a node (filename) after redirection */
int	what_after_filename(t_list_of_tok *node)
{
	if (node == NULL)
	//	return (printf("No token after node\n"), 0);
	return (0);
	//printf("Token after node is: %s\n", node->token);
	// Check if the token after the node is a command or built-in
	if (node->type == T_COMMAND || node->type == T_BUILTIN)
	//	return (printf("Command or built-in found after node\n"), 1);
	return (1);
	// If the next token is not a command or built-in, return 2
	//return (printf("No command or built-in after node\n"), 2);
	return (2);
}


/* always pass a valid pointer, otherwise segfault */
int	is_a_redirection(t_list_of_tok *token)
{
	if (token->type == T_REDIR_OUT || token->type == T_REDIR_IN || token->type == T_REDIR_APP)
		return (1); // it means true
	else
		return (0); // in this case means false
}
void	find_empty_redirection(t_list_of_tok **head)
{
	t_list_of_tok	*current;
	t_list_of_tok	*prev;
	t_list_of_tok	*next;
	int				after_filename;

	after_filename = 0;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		prev = current->previous;
		// Check if the current node is a redirection
		if (is_a_redirection(current))
		{
			/*printf("\t%scurrent (%s) index: %d %s\n", BG_YELLOW, current->token, current->index, BG_RESET);
			if (prev)
				printf("has before (%s)", prev->token);
			if (next)
				printf("and after (%s)\n", next->token); */
			// Check if the previous node is not a command, flag, or command argument
			// and if the next node is not a command, flag, or command argument
//			printf("\n\t[%sPerforming check on prev and next%s]\n", GREEN, RESET);
			if (next->next)
				after_filename = what_after_filename(next->next);
			if (is_valid_prev(prev) == 0 && is_valid_next(next) == 0 && after_filename != 1)
			{
				// Create an "EMPTY" node and insert it before the current node
				printf("\n%sthe code would insert an empty node%s\n\n\n", YELLOW, RESET);
				// Insertion logic here
				// Create an "EMPTY" node and insert it before the current node
				t_list_of_tok *empty_node = create_empty_node();
				empty_node->next = current;
				empty_node->previous = prev;
				if (prev)
					prev->next = empty_node;
				else
					*head = empty_node; // Update head if it was the first node
				current->previous = empty_node;
			}
		}
		current = current->next;
	}
}

void	swap_redirection_with_command(t_list_of_tok **head)
{
	t_list_of_tok *current = *head;
	t_list_of_tok *redir_node = NULL;
	t_list_of_tok *file_node = NULL;
	t_list_of_tok *command_node = NULL;
//	printf("swap redirection is being called\n");
	// Traverse the list to find the redirection and file nodes
	while (current)
	{
		if (is_a_redirection(current))
		{
			redir_node = current;
			file_node = current->next; // Assuming the file node always follows the redirection node
		}
		else if ((current->type == T_COMMAND || current->type == T_BUILTIN) && file_node && my_strcmp("EMPTY", current->token) != 0)
		{
			command_node = current;
			break;
		}
		current = current->next;
	}

	// If we found a command after a file name, perform the swap
	if (command_node && file_node && redir_node)
	{
//		printf("swap is being performed\n");
//		move_node(head, redir_node, command_node);
		move_node_fix(head, redir_node, command_node);
		/*
		// Remove the command node from its current position
		remove_node(head, command_node);
		// Insert the command node before the redirection node
		insert_after_node(redir_node->previous, command_node);
		// Reconnect the file node to the redirection node
		insert_after_node(command_node, redir_node);
		*/
	}
}


t_list_of_tok	**update_list_order(t_list_of_tok **head)
{
	if (find_command_in_list(head) == NULL)
		find_empty_redirection(head);
	swap_redirection_with_command(head);
	return (head);
}
