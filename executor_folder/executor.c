/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:25:22 by atucci            #+#    #+#             */
/*   Updated: 2024/01/20 23:33:48 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"
#include "../minishell.h"
int	g_exit_status;

/* 5 function in this file 
 * This function goes throught he list and look for commands,
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
*/
t_list_of_tok	*open_file(t_list_of_tok *nod)
{
	int	fd;

	if (nod->type == T_REDIR_OUT)
		fd = open(nod->next->token, OVERWRITE_FLAGS, 0666);
	else
		fd = open(nod->next->token, APPEND_FLAGS, 0666);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (nod);
}

/* function to find the last redirection, if there is more, open empty file */
int	find_redirect(t_list_of_tok *cmd_node)
{
	t_list_of_tok	*iterator;
	t_list_of_tok	*last_redirect;

	last_redirect = NULL;
	iterator = cmd_node;
	while (iterator != NULL)
	{
		if (iterator->type == T_REDIR_OUT || iterator->type == T_REDIR_APP || iterator->type == T_REDIR_IN || iterator->type == T_HERE_DOC)
		{
			if (iterator->next == NULL)
				return (set_g_exit(GENERAL_ERROR), printf("minishesh: parse error near '\\n\'\n"), 1);
			if (iterator->next->type == T_FILE_NAME)
				last_redirect = open_file(iterator);
		}
		iterator = iterator->next;
	}
	if (last_redirect != NULL)
	{
		cmd_node->file_name = ft_strdup(last_redirect->next->token);
		cmd_node->redirect_type = last_redirect->type;
		return (0);
	}
	return (0);
}

/*3)
 this fuction handle the redirection process
 redirection_process(current, current->next->type);
 */
int	redirection_process(char *file_name, t_type_of_tok type)
{
	if (type == T_REDIR_IN)
		if (redirect_input(file_name))
			return (1);
	if (type == T_REDIR_OUT || type == T_REDIR_APP)
		redirect_output(file_name, type);
	if (type == T_HERE_DOC)
	{
		printf("here doc \n");
		here_document(file_name);
	}
	return (0);
}

/* this function is suppose to handle the piping if
 * the fd are differente than the standards
*/
void	piping_process(t_list_of_tok *cmd_nod)
{
	if (cmd_nod->index != 0)
	{
		dup2(cmd_nod->in_file, STDIN_FILENO);
		close(cmd_nod->in_file);
	}
	if (cmd_nod->out_file != 1)
	{
		dup2(cmd_nod->out_file, STDOUT_FILENO);
		close(cmd_nod->out_file);
	}
}

/* last change */
void	restore_original_stdout(int copy, t_list_of_tok *cmd_nod)
{
	(void)cmd_nod;
	dup2(copy, STDOUT_FILENO);
	close(copy);
}

void	restore_original_stdin(int copy, t_list_of_tok *cmd_nod)
{
	(void)cmd_nod;
	dup2(copy, STDIN_FILENO);
	close(copy);
}

/* 2)
 * first handle the redirection
 * then check for builtins, after perform built in, restore fd (?)
 * otherwise fork and go on with execve, after that restore fd (?)
*/
void	*execute_command(char *command, char **args_a, char **envp, t_list_of_tok *cmd_nod)
{
	pid_t	fix_pid;
	int		stdout_copy;
	int		stdin_copy;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	piping_process(cmd_nod);
	if (cmd_nod->file_name != NULL)
		if (redirection_process(cmd_nod->file_name, cmd_nod->redirect_type))
			return (NULL);
	if (cmd_nod->type == T_BUILTIN)
		which_built_in(cmd_nod, args_a, envp);
	else
	{
		fix_pid = fork();
		if (fix_pid == 0)
		{	
			//if (cmd_nod->index <= 2)
			if (my_strcmp(cmd_nod->token, "cat") == 0 && cmd_nod->next) // work on this edge cases
			{
				// penultimo comando ...
				ft_putstr_fd("Next->next token [ ", stdout_copy);
				ft_putstr_fd(cmd_nod->next->next->token, stdout_copy);
				ft_putstr_fd(" ] \n", stdout_copy);
				//printf("closing the infile of node: (%s)\n", cmd_nod->next->next->token);
				close(cmd_nod->next->next->in_file);
			}
			close(stdin_copy);
			close(stdout_copy);
			execve(command, args_a, envp);
			printf("command not found: %s\n", command);
			set_g_exit(COMMAND_NOT_FOUND);
		}
	}
	restore_original_stdout(stdout_copy, cmd_nod);
	restore_original_stdin(stdin_copy, cmd_nod);
	return (NULL);
}

/*
 * 1) Main function to execute the program
 * I go find the first command in the list
 * Inside the node of the command I update the filename
 * if there is a redirection, the command string take the
 * token of the node 
 * 
 */
void	update_exit_status()
{
	int	status;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}

int	executor(t_list_of_tok **head, char **envp)
{
	char			*command;
	char			**argoums;
	t_list_of_tok	*cmd_node;

	cmd_node = find_command_in_list(head);
	while (cmd_node != NULL)
	{
		if (find_redirect(cmd_node) == 1)
			break ;
		find_pipes(cmd_node);
		command = cmd_node->token;
		if (cmd_node->type != T_BUILTIN)
		{
			command = find_path_command(cmd_node->token, envp);
			if (command == NULL)
				command = cmd_node->token;
		}
		argoums = array_from_list(&cmd_node);
		execute_command(command, argoums, envp, cmd_node);
		cmd_node = find_command_in_list(&cmd_node->next);
	}
	update_exit_status(); // osema extra work
	return (0);
}
