/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:25:22 by atucci            #+#    #+#             */
/*   Updated: 2023/12/27 12:31:53 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**find_path_env(char **env)
{
	int	i;
	char *nully = NULL;
	(void)env;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			nully = env[i] + 5;
			break ;
		}
		i++;
	}
	//printf("path env: |%s%s%s|\n",YELLOW, nully, RESET);
	return (ft_split(nully, ':'));
}

t_list_of_tok	*find_command_in_list(t_list_of_tok **head)
{
	t_list_of_tok	*current;

	current = *head;
	while (current != NULL)
	{
		if (current->type == T_COMMAND || current->type == T_BUILTIN)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/* this functinon needs to be written entirely */
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
/*an other suggestive suggestion */
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

/* this fuction handle the redirection process */
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
		printf("handling PIPES case\n");
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

void	executor(t_list_of_tok **head, char **envp)
{
	int		i;
	int		y;
	char	**directs;
	char	*command = NULL;
	char	*possible_command;

	t_list_of_tok *current = find_command_in_list(head);
	if (current == NULL)
	{
		printf("there is no command in the string sadly\n");
		return ;
	}
	// I need to check for pipes and redirections
	current->file_name = find_pipe_redirect(current);
	printf("FILE TO OPEN | COMMAND TO TAKE: %s%s%s\n", YELLOW, current->file_name, RESET);
	
	i = 0;
	directs = find_path_env(envp);
	while (directs[i] != NULL)
	{
		y = ft_strlen(directs[i]) + ft_strlen(current->command_as_string) + 2;
		possible_command = malloc(ft_strlen(directs[i]) + ft_strlen(current->command_as_string) + 2); // +2 for the '/' and '\0'
		ft_strlcpy(possible_command, directs[i], y);
		ft_strlcat(possible_command, "/", y);
		ft_strlcat(possible_command, current->command_as_string, y);
		if (access(possible_command, X_OK) == 0)// Check if the command is executable
		{
			command = possible_command;
			break;
		}
		free(possible_command);
		i++;
	}
	// I need to create a array of string to pass to the execve!
	char **test = argv_for_exceve(head);
/*                                                                           */
		if (fork() == 0)
		{
			if (current->file_name != NULL)
				redirection_process(current, current->next->type);
			execve(command, test, envp);
			perror("execve");// execve returns only on error
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);// parent waits for the child to finish
		free(command);
/*                                                                          */
	executor2();
	executor3();
	return ;
}
