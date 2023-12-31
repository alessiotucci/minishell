/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:25:22 by atucci            #+#    #+#             */
/*   Updated: 2023/12/31 17:24:32 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/* 5 function in this file */
t_list_of_tok	*find_command_in_list(t_list_of_tok **head)
{
	t_list_of_tok	*current;

	current = *head;
	while (current != NULL)
	{
		if (current->type == T_COMMAND || current->type == T_BUILTIN)
			return (current);
		//if (current->type == T_BUILTIN)
		//	which_built_in(current);
		current = current->next;
	}
	return (NULL);
}

/* 4) this functinon needs to be written entirely */
char *find_pipe_redirect(t_list_of_tok *iterator)
{
	char	*found;

	found = NULL;
	while (iterator != NULL)
	{
		if (iterator->type == T_PIPES || iterator->type == T_REDIR_OUT || iterator->type == T_REDIR_APP || iterator->type == T_REDIR_IN)
		{
			if (iterator->next == NULL)
			{
				printf("Syntax error: unexpected end of command\n");
				return (NULL);
			}
			iterator->file_name = ft_strdup(iterator->next->command_as_string);
			found = ft_strdup(iterator->file_name); // remember to free it
		}
		iterator = iterator->next;
	}
	return (found);
}
/*3) an other suggestive suggestion */
void find_pipe_redirecty(t_list_of_tok *head)
{
	// Create a pointer to traverse the list
	t_list_of_tok *current_node = head;
	// Print a message indicating the start of pipe or redirection check
	printf("%sChecking for pipes or redirection%s\n", RED, RESET);
	// Iterate through the list
	while (current_node != NULL)
	{
		// Check if the current node is a pipe or redirection operator
		if (current_node->type == T_PIPES || current_node->type == T_REDIR_OUT || current_node->type == T_REDIR_APP || current_node->type == T_REDIR_IN)
		{
			// If there's no next node, print an error message and return
			if (current_node->next == NULL)
			{
				printf("Syntax error: unexpected end of command\n");
				return;
			}
			// Save the type of operator in the current node
			current_node->type = current_node->next->type;
			// Save the filename or command in the current node
			current_node->file_name = ft_strdup(current_node->next->command_as_string);
			// Skip the next node as we've already processed it
			current_node->next = current_node->next->next;
		}
		// Move to the next node
		current_node = current_node->next;
	}
	// End of function, no return value needed as function is void
}

/*2)
 this fuction handle the redirection process
 redirection_process(current, current->next->type);
 */
void	redirection_process(t_list_of_tok *current, t_type_of_tok type)
{
	if (type == T_FLAG || type == T_COMMAND_ARGS)
		redirection_process(current->next, current->next->type);
		// handle the case if there is a flag
	if (type == T_REDIR_IN)
	{
		printf("redirect the input\n");
		redirect_input(current->file_name);
	}
	else if (type == T_REDIR_OUT || type == T_REDIR_APP)
	{
		printf("redirect the output\n");
		redirect_output(current, type);
	}
	else if (type == T_PIPES)
	{
		printf("handling PIPES case\n");
		printf("%s%s%s\n", GREEN,current->file_name, RESET);
		//pipex(current, current->next);
	}
	else if (type == T_HERE_DOC)
	{
		printf("handling HERE_DOC case\n");
		here_document(current->file_name);
	}
	else
	{
		printf("%sthere might be a issue [%s]%s\n", RED, current->command_as_string, RESET);
		print_node(current);
	}
}

/* 1) Main function to execute the program */
int	executor(t_list_of_tok **head, char **envp)
{
	int		i;
	char	*command;
	char	**test;

	t_list_of_tok *current = find_command_in_list(head); // in this line the builtin take over
	if (current == NULL)
		return (printf("there is no command in the string sadly\n"));
	current->file_name = find_pipe_redirect(current);
	command = current->command_as_string;
//	printf("FILE TO OPEN | COMMAND TO TAKE: %s%s%s\n", YELLOW, current->file_name, RESET);
	i = 0;
	if (current->type != T_BUILTIN)
		command = find_possible_command(current->command_as_string, envp);
	if (command == NULL)
		return (free(command), printf("the commmand is null\n"));
	test = argv_for_exceve(head);
/*	printf("**%s Let's the debugging start ! ***%s \n", BG_GREEN, BG_RESET);
	printf("command: [%s]", command);
	print_string_array(test);
	print_node(current);
	printf("**%s finished with the debugging!***%s \n", BG_RED, BG_RESET); */
	execute_command(command, test, envp, current);
//	free(command);
	executor2();
	executor3();
	return (0);
}
