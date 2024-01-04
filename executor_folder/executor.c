/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:25:22 by atucci            #+#    #+#             */
/*   Updated: 2024/01/04 11:25:59 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 5 function in this file 
 * This function goes through the list and look for commands,
 * it return the first it finds !
 * */
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

/* 4) this functinon needs to be written entirely 
 * it has being copy and paste from bingAi again
 *
 * */
char *find_pipe_redirect(t_list_of_tok *iterator)
{
	char	*found;
	int	pipefd[2];

	found = NULL;
	while (iterator != NULL)
	{
		if (iterator->type == T_PIPES)
		{
			if (iterator->next == NULL)
				return (NULL);
			if (pipe(pipefd) == -1)
				return (NULL);
			iterator->fd_redirect = pipefd[1];
			found = ft_strdup(iterator->file_name); // remember to free it
		}
		else if (iterator->type == T_REDIR_OUT || iterator->type == T_REDIR_APP || iterator->type == T_REDIR_IN)
		{
			if (iterator->next == NULL)
				return (NULL);
			iterator->file_name = ft_strdup(iterator->next->token);
			found = ft_strdup(iterator->file_name); // remember to free it
		}
		iterator = iterator->next;
	}
	return (found);
}

/*3)
 this fuction handle the redirection process
 redirection_process(current, current->next->type);
 */
void	redirection_process(t_list_of_tok *current, t_type_of_tok type)
{
	if (type == T_FLAG || type == T_COMMAND_ARGS)
		redirection_process(current->next, current->next->type);
	if (type == T_REDIR_IN)
		redirect_input(current->file_name);
	else if (type == T_REDIR_OUT || type == T_REDIR_APP)
		redirect_output(current, type);
	else if (type == T_PIPES)
	{
		printf("handling PIPES case\n");
		printf("%s%s%s\n", GREEN, current->file_name, RESET);
		//pipex(current, current->next);
	}
	else if (type == T_HERE_DOC)
		here_document(current->file_name);
	else
		print_node(current);
}

/* 2)
 * first handle the redirection
 * then check for builtins, after perform built in, restore fd (?)
 * otherwise fork and go on with execve, after that restore fd (?)
*/
void	*execute_command(char *command, char **test, char **envp, t_list_of_tok *current)
{
	pid_t	fix_pid;
	int	stdout_copy = dup(STDOUT_FILENO);

	if (current->file_name != NULL)
		redirection_process(current, current->next->type); // here the fd are changed
	if (current->type == T_BUILTIN)
	{
		which_built_in(current);
		// Restore the original stdout file descriptor
		dup2(stdout_copy, STDOUT_FILENO);
		close(stdout_copy);
		return NULL;
	}
	else
	{
		fix_pid = fork();
		if (fix_pid == 0)
		{
			execve(command, test, envp);
			perror("execve"); // execve returns only on error
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);
	}
dup2(stdout_copy, STDOUT_FILENO);
close(stdout_copy);
return (NULL);
}

/* 1) Main function to execute the program */
int	executor(t_list_of_tok **head, char **envp)
{
	char	*command;
	char	**argoums;
	t_list_of_tok *current;
	//char	*file_name;
	current = find_command_in_list(head);
	if (current == NULL)
		return (printf(" "));
	current->file_name = find_pipe_redirect(current);
	command = current->token;
	if (current->type != T_BUILTIN)
		command = find_path_command(current->token, envp);
	if (command == NULL)
		return (free(command), printf("the commmand is null\n"));
	argoums = array_from_list(head);
	execute_command(command, argoums, envp, current);
	return (0);
}
