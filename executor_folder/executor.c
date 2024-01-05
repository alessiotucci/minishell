/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:25:22 by atucci            #+#    #+#             */
/*   Updated: 2024/01/05 11:58:16 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 5 function in this file 
 * This function goes through the list and look for commands,
 * it return the first it finds !
 * */
t_list_of_tok	*find_command_in_list(t_list_of_tok **head)
{
	t_list_of_tok	*cmd_nod;

	cmd_nod = *head;
	while (cmd_nod != NULL)
	{
		if (cmd_nod->type == T_COMMAND || cmd_nod->type == T_BUILTIN)
			return (cmd_nod);
		cmd_nod = cmd_nod->next;
	}
	return (NULL);
}

/* 4) this functinon needs to be written entirely 
 * it has being copy and paste from bingAi again
 *
 * */
char *find_redirect(t_list_of_tok *iterator)
{
	char	*found;

	found = NULL;
	while (iterator != NULL)
	{
		if (iterator->type == T_REDIR_OUT || iterator->type == T_REDIR_APP || iterator->type == T_REDIR_IN)
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
void	redirection_process(t_list_of_tok *cmd_nod, t_type_of_tok type)
{
	if (type == T_FLAG || type == T_COMMAND_ARGS)
		redirection_process(cmd_nod->next, cmd_nod->next->type);
	if (type == T_REDIR_IN)
		redirect_input(cmd_nod->file_name);
	else if (type == T_REDIR_OUT || type == T_REDIR_APP)
		redirect_output(cmd_nod, type);
	else if (type == T_HERE_DOC)
		here_document(cmd_nod->file_name);
//	else
//		print_node(cmd_nod);
}

/* 2)
 * first handle the redirection
 * then check for builtins, after perform built in, restore fd (?)
 * otherwise fork and go on with execve, after that restore fd (?)
*/
void	*execute_command(char *command, char **args_a, char **envp, t_list_of_tok *cmd_nod)
{
	pid_t	fix_pid;
//	int	stdout_copy = dup(STDOUT_FILENO);

	if (cmd_nod->file_name != NULL)
		redirection_process(cmd_nod, cmd_nod->next->type); // here the fd are changed
	if (cmd_nod->type == T_BUILTIN)
	{
		printf("Builtin fd is %d\n\n\n", cmd_nod->fd_pipe);
		which_built_in(cmd_nod, args_a, envp);
		// Restore the original stdout file descriptor
		//dup2(stdout_copy, STDOUT_FILENO);
		//close(stdout_copy);
		return NULL;
	}
	else
	{
		printf("Command fd is %d\n\n\n", cmd_nod->fd_pipe);
		fix_pid = fork();
		if (fix_pid == 0)
		{
			execve(command, args_a, envp);
			perror("execve"); // execve returns only on error
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);
	}
//dup2(stdout_copy, STDOUT_FILENO);
//close(stdout_copy);
return (NULL);
}

/* 1) Main function to execute the program
 * I go find the first command in the list
 * Inside the node of the command I update the filename
 * if there is a redirection, the command string take the
 * token of the node 
 * */
int	executor(t_list_of_tok **head, char **envp)
{
	char			*command;
	char			**argoums;
	t_list_of_tok	*cmd_node;

	cmd_node = find_command_in_list(head);
	while (cmd_node != NULL)
	{
		cmd_node->file_name = find_redirect(cmd_node);
		find_pipes(cmd_node);
		command = cmd_node->token;
		if (cmd_node->type != T_BUILTIN)
			command = find_path_command(cmd_node->token, envp);
		if (command == NULL)
			return (free(command), printf(" Command not found: %s\n", cmd_node->token));
		argoums = array_from_list(head);
		execute_command(command, argoums, envp, cmd_node);
		cmd_node = find_command_in_list(&cmd_node->next);
	}
	return (0);
}
