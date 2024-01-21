/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_order_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 19:21:22 by atucci            #+#    #+#             */
/*   Updated: 2024/01/21 14:24:01 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_a_redirection(t_list_of_tok *token);

/*5)  Helper function to create a new node */
t_list_of_tok	*create_empty_node(void)
{
	t_list_of_tok	*new_node;

	new_node = (t_list_of_tok *)malloc(sizeof(t_list_of_tok));
	if (new_node == NULL)
		return (printf("Error with malloc"), NULL);
	new_node->token = "EMPTY";
	new_node->type = T_BUILTIN;
	new_node->priority_lev = 0;
	new_node->next = NULL;
	new_node->previous = NULL;
	new_node->index = -1;
	new_node->file_name = NULL;
	new_node->in_file = STDIN_FILENO;
	new_node->out_file = STDOUT_FILENO;
	return (new_node);
}

/* 4 Determine what follows a node (filename) after redirection */
/* called with the node afte the filename */
int	what_after_filename(t_list_of_tok *file_node)
{
	if (file_node == NULL)
		return (0); // dopo il filename non cé nulla;
	if (file_node->type == T_COMMAND || file_node->type == T_BUILTIN)
		return (1);
	return (2);
}


/*3) function that looks for empty redirection */
void	find_empty_redirection(t_list_of_tok **head)
{
	t_list_of_tok	*current;
	t_list_of_tok	*prev;
	t_list_of_tok	*next;
	t_list_of_tok	*empty_node;
	int				after_filename;

	after_filename = 0;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		prev = current->previous;
		if (is_a_redirection(current))
		{
			if (next->next)
				after_filename = what_after_filename(next->next);
			if (is_valid_prev(prev) == 0 && is_valid_next(next) == 0 && after_filename != 1)
			{
				//printf("\n%sthe code would insert an empty node%s\n\n\n", YELLOW, RESET);
				empty_node = create_empty_node();
				empty_node->next = current;
				empty_node->previous = prev;
				if (prev)
					prev->next = empty_node;
				else
					*head = empty_node;
				current->previous = empty_node;
			}
		}
		current = current->next;
	}
}
/* 2) function that swap the node, keeping in mind those edge cases */
void	swap_redirection_with_command(t_list_of_tok **head)
{
	t_list_of_tok	*current;
	t_list_of_tok	*redir_node;
	t_list_of_tok	*file_node;
	t_list_of_tok	*command_node;

	current = *head;
	redir_node = NULL;
	file_node = NULL;
	command_node = NULL;
//	printf("swap redirection is being called\n");
	while (current)
	{
		if (is_a_redirection(current))
		{
			redir_node = current;
			file_node = current->next;
		}
		else if ((current->type == T_COMMAND || current->type == T_BUILTIN) && file_node && my_strcmp("EMPTY", current->token) != 0)
		{
			command_node = current;
			break;
		}
		current = current->next;
	}
	if (command_node && file_node && redir_node)
		move_node(head, redir_node, command_node);
}

int should_swap(t_list_of_tok *head)
{
	t_list_of_tok *current = head;
	while (current != NULL)
	{
		if (is_a_redirection(current) && current->next != NULL && current->next->type == T_FILE_NAME)
		{
			t_list_of_tok *command_node = current->next->next;
			printf("command_node token [%s]\n", command_node->token);
			if (command_node != NULL && (command_node->type == T_COMMAND || command_node->type == T_BUILTIN))
			{
				t_list_of_tok *next_node = command_node->next;
				if (next_node == NULL || is_a_redirection(next_node) || next_node->type == T_PIPES || next_node->type == T_FLAG || next_node->type == T_COMMAND_ARGS)
				{
					printf("the code would swap a node\n");
					return 1;
				}
			}
		}
		else if ((current->type == T_COMMAND || current->type == T_BUILTIN)
			&& current->next != NULL && is_a_redirection(current->next) && what_after_filename(current->next->next->next) == 1)
		{
			printf("else\n");
			// If a command node is followed by a redirection node, also return 1
			//printf("1the code would swap a node\n");
			return 1;
		}
		current = current->next;
	}
	printf("the code would NOT swap node\n");
	return 0;
}


/*1) function to update the order of the list */
t_list_of_tok	**update_list_order(t_list_of_tok **head)
{
	if (find_command_in_list(head) == NULL)
		find_empty_redirection(head);
//	printf("swapping when there is no need\n");
//	printf("I should check the order of command and redirection\n");
	if (should_swap(*head))
	swap_redirection_with_command(head);
	return (head);
}
